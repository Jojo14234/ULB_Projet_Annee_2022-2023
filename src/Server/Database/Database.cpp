#include <algorithm>
#include <memory>

#include "Database.hpp"
#include "User/User.hpp"
#include "Chat/Conversation.hpp"


void Database::load() {
	FILE *file = std::fopen(path.c_str(), "rb");


	if (!file) {
        this->data.reserve(EMPTY_DATABASE_RESERVE_SPACE);
        std::cout << "Database empty !" << std::endl;
        return;
    }


	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	this->data.reserve(size + size/RESERVE_SPACE_SUPP);
	for (size_t i = 0; i < size; i++) {
		std::shared_ptr<User> user = std::make_shared<User>();
		user->read(file);
		this->data.push_back(user);
	}
	std::fclose(file);
	std::cout << "Database loaded : [" << this->getSize() << " account registered]" << std::endl;
}

void Database::save() {
	this->user_am.lockReader();
	FILE *file = std::fopen(path.c_str(), "w+");

    // The file was not open properly
    if (!file) {
        // Impossible en théorie fOpen crée un fichier s'il n'existe pas.
        std::cout << "Database not saved [ (" << path << ") didn't open properly]" << std::endl;
        return;
    }

    // The file was open properly
    size_t size = this->data.size();
	fwrite(&size, sizeof(size_t), 1, file);
    for (auto user : this->data) {
        user->write(file);
    }
	std::fclose(file);
	std::cout << "Database saved : [" << this->getSize() << " account saved]"<< std::endl;
	this->user_am.unlockReader();
}

bool Database::contains(const int id) const {
	this->user_am.lockReader();
	for (const auto &user : this->data) {
		if (user->isId(id)) { return true; }
	} this->user_am.unlockReader(); return false;
}

bool Database::contains(const char username[32]) const {
	this->user_am.lockReader();
	for (const auto &user : this->data) {
		if (user->isUsername(username)) { return true; }
	} this->user_am.unlockReader(); return false;
}

User* Database::getUser(const int id) {
	this->user_am.lockReader();
	for (auto &user : this->data) {
		if (user->isId(id)) { this->user_am.unlockReader(); return user.get(); }
	} this->user_am.unlockReader(); return nullptr;
}

User* Database::getUser(const char username[32]) {
	this->user_am.lockReader();
	for (auto &user : this->data) {
		if (user->isUsername(username)) { this->user_am.unlockReader(); return user.get(); }
	} this->user_am.unlockReader(); return nullptr;
}

std::string Database::getUsername(const int id) { return this->getUser(id)->getUsername(); }

User* Database::addUser(std::string username, std::string password) {
	this->user_am.lockWriter();
	std::shared_ptr<User> user = std::make_shared<User>(this->getSize()+1, username.c_str(), password.c_str());
    this->data.push_back(user);
	this->user_am.unlockWriter();
    this->save();
    return user.get();
}

void Database::print_in_file() {
	std::ofstream file("clear.txt", std::ios::out | std::ios::trunc);
	if (file) {
		for (auto &user : this->data) file << std::string{*user} << std::endl;
	}
	file.close();
}

int Database::getRankingPos(const User* user) {
    this->sortByRank(this->data.size());
	int idx = 1;
    for (auto u : this->data) {
        if (u.get() == user) { return idx; }
        idx++;
    }
	return idx;
}

void Database::emplace(const User* user, std::array<const User*, 5> &bests) {
	for (short unsigned int i = 0; i < 5; i++) {
		if (user->getStats() > bests[i]->getStats()) {
			for (short unsigned int j = 5; j < i; j--) bests[j] = bests[j-1];
			bests[i] = user;
		}
	}
}

std::array<const User*, 5> Database::getRanking() {
    this->sortByRank(this->data.size());
	std::array<const User*, 5> bests{nullptr, nullptr, nullptr, nullptr, nullptr};
	this->user_am.lockReader();
	for (short unsigned i = 0; i < 5; i++) bests[i] = this->data[i].get();
	this->user_am.unlockReader();
	return bests;
}

std::string Database::getRankingTopString() {
    std::array<const User*, 5> top = this->getRanking();
    std::string input = "";
    for (int i=0; i < 5 && top[i] != nullptr ; i++) {
        input += this->getRankingPosString(top[i], i);
    }
    return input;
}

std::string Database::getRankingPosString(const User *user, int pos) {
    std::string input = "";
    int position = (pos == -1) ? this->getRankingPos(user) : pos;
    input += std::to_string(position) + ":";
    input += user->getUsername() + ":";
    input += std::to_string(user->getStats().getScore()) + "|";
    return input;
}

void Database::sortByRank(unsigned int size) {
    bool sorted = true;
    this->user_am.lockReader();
    for (unsigned int j = 0; j < size - 1; j++) {
        if (this->data[j]->getStats() < this->data[j+1]->getStats()) {
            std::shared_ptr<User> tmp = this->data[j];
            this->data[j] = this->data[j+1];
            this->data[j+1] = tmp;
            sorted = false;
        }
    }
    this->user_am.unlockReader();
    if (!sorted) { this->sortByRank(size); }
}

void Database::resetRanking() {
    for ( auto &user : this->data ) {
        user->resetStats();
    }
}

void Database::addUser(User user) { this->data.push_back(std::make_shared<User>(user)); }

bool Database::contains(const User &user) const { return this->contains(user.getId()); }

Conversation* Database::createConv(User* sender, User* receiver) {
	this->chat_am.lockWriter();
	Conversation &conv = this->chat.emplace_back(sender, receiver);
	this->chat_am.unlockWriter();
	return &conv;
}

Conversation* Database::getConv(User* sender, User* receiver) {
	if (sender == nullptr or receiver == nullptr) { return nullptr; }
	this->chat_am.lockReader();
	for (auto &conv : this->chat) {
		if (conv.isATalker(sender) and conv.isATalker(receiver)) {
			return &conv;
		}
	} this->chat_am.unlockReader(); return nullptr;
}

void Database::sendMsg(User* sender, User* receiver, const std::string &msg) {
	Conversation* conv = this->getConv(sender, receiver);
	if (conv == nullptr) { conv = this->createConv(sender, receiver); }
	conv->addMsg(sender, msg);
}

#include <algorithm>

#include "Database.hpp"
#include "User.hpp"
#include "Chat/Conversation.hpp"


void Database::load() {
	FILE *file = std::fopen(path.c_str(), "rb");
	if (!file) { this->data.reserve(10); std::cout << "Database empty !" << std::endl; return; }
	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	this->data.reserve(size + size/4);
	for (size_t i = 0; i < size; i++) {
		User user;
		user.read(file);
		this->data.push_back(user);
	}
	std::fclose(file);
	std::cout << "Database loaded : [" << this->getSize() << " account registered]" << std::endl;
}

void Database::save() {
	this->user_am.lockReader();
	FILE *file = std::fopen(path.c_str(), "w+");
	if (!file) exit(0);
	size_t size = this->data.size();
	fwrite(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) this->data[i].write(file);
	std::fclose(file);
	std::cout << "Database saved : [" << this->getSize() << " account saved]"<< std::endl;
	this->user_am.unlockReader();
}

bool Database::contains(const int id) const {
	this->user_am.lockReader();
	for (const auto &user : this->data) {
		if (user.isId(id)) { return true; }
	} this->user_am.unlockReader(); return false;
}

bool Database::contains(const char username[32]) const {
	this->user_am.lockReader();
	for (const auto &user : this->data) {
		if (user.isUsername(username)) { return true; }
	} this->user_am.unlockReader(); return false;
}

User* Database::getUser(const int id) {
	this->user_am.lockReader();
	for (auto &user : this->data) {
		if (user.isId(id)) { this->user_am.unlockReader(); return &user; }
	} this->user_am.unlockReader(); return nullptr;
}

User* Database::getUser(const char username[32]) {
	this->user_am.lockReader();
	for (auto &user : this->data) {
		if (user.isUsername(username)) { this->user_am.unlockReader(); return &user; }
	} this->user_am.unlockReader(); return nullptr;
}

std::string Database::getUsername(const int id) { return this->getUser(id)->getUsername(); }

User* Database::addUser(std::string username, std::string password) {
	this->user_am.lockWriter();
	User &user = this->data.emplace_back(this->getSize()+1, username.c_str(), password.c_str());
	this->user_am.unlockWriter();
	return &user;
}

void Database::print_in_file() {
	std::ofstream file("clear.txt", std::ios::out | std::ios::trunc);
	if (file) {
		for (auto &user : this->data) file << std::string{user} << std::endl;
	}
	file.close();
}

int Database::getRankingPos(User* user) {
	int idx = 0;
	for (auto &u : this->data) if (u.getStats() > user->getStats()) idx++;
	return idx + 1;
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
	std::array<const User*, 5> bests{nullptr, nullptr, nullptr, nullptr, nullptr};
	this->user_am.lockReader();
	for (short unsigned i = 0; i < 5; i++) bests[i] = &(this->data[i]);
	std::sort(bests.begin(), bests.end(),
		[](const User* a, const User* b) { 
			if (a == nullptr || b == nullptr) return false;
			if (a == nullptr) return true;
			if (b == nullptr) return false;
			return a->getStats() > b->getStats();
		}
	);
	for (const auto &u : this->data) this->emplace(&u, bests);
	this->user_am.unlockReader();
	return bests;
}

void Database::addUser(User user) { this->data.push_back(user); }

void Database::removeUser(User &user) {
	this->user_am.lockWriter();
	auto it = std::find(this->data.begin(), this->data.end(), user);
	this->data.erase(it);
	this->user_am.unlockWriter();
}

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

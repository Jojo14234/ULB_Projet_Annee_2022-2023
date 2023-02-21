#include "Database.hpp"
#include "User.hpp"
#include "Chat/Conversation.hpp"


void Database::load() {
	FILE *file = std::fopen(path, "rb");
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
	FILE *file = std::fopen(path, "w+");
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
	User* user = this->data.emplace_back(this->getSize()+1, username.c_str(), password.c_str());
	this->user_am.unlockWriter();
	return user;
}

void Database::print_in_file() {
	std::ofstream file("clear.txt", std::ios::out | std::ios::trunc);
	if (file) {
		for (auto &user : this->data) {file << user.toString() << std::endl;}
	}
	file.close();
}

void bubble_sort(std::vector<User> &data) {
    for (unsigned i=0; i < data.size(); i++) {
        for (unsigned j=0; j < data.size() - i; j++) {
            if (data[j].getStats() > data[j+1].getStats()) {
                std::swap(data[j], data[j+1]);
            }
            // Dans le cas d'une égalité, on prend le score moyen (score/nb_game)
            else if (data[j].getStats().getScore() == data[j+1].getStats().getScore()) {
                if (data[j].getStats().calculateMiddleScore() > data[j+1].getStats().calculateMiddleScore()) {
                    std::swap(data[j], data[j+1]);
                }
            }
        }
    }
}

void Database::getRanking(std::vector<User*> &ranking) {
    // 1. Créer une copie de la db
    std::vector<User> data_copy;
    for (auto user : data) {data_copy.push_back(user);}

    // 2. Trié ce nouveau vecteur
    bubble_sort(data_copy);
    // 3. Récupérer les id des 5 premiers dans la db trié
    unsigned j=0;
    while (j <= data_copy.size() || j < 5) {
        // 4. Chercher dans la vraie db les 5 id
        User* user = getUser(data_copy[data_copy.size()-j].getId());
        // 5. Ajouter leur adresse à un vecteur
        ranking.push_back(user);
        j++;
    }
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

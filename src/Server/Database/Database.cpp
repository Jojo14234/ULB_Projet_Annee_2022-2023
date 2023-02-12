#include "Database.hpp"
#include "User.hpp"


void Database::load() {
	this->am.lockWriter();
	FILE *file = std::fopen(path, "rb");
	if (!file) { this->data.reserve(10); std::cout << "Database empty !" << std::endl; return; }
	this->data.reserve(this->fileSize(file)/sizeof(User));
	User user;
	while (std::fread(&user, sizeof(User), 1, file)) this->data.push_back(user);
	std::fclose(file);
	std::cout << "Database loaded : [" << this->getSize() << " account registered]" << std::endl;
	this->am.unlockWriter();
}

size_t Database::fileSize(FILE *file) {
	// Save the start position of the db file
	size_t cursor = std::ftell(file);
	// Place the cursor at the end of the file
	std::fseek(file, 0, SEEK_END);
	// Get the file size
	size_t size = std::ftell(file);
	// Replace the cursor at the start
	std::fseek(file, 0, cursor);
	return size;
}

void Database::save() {
	this->am.lockReader();
	FILE *file = std::fopen(path, "w+");
	if (!file) exit(0);
	if (std::fwrite(data.data(), sizeof(User), data.size(), file) != data.size()) std::cout << "Database not saved" << std::endl;
	std::fclose(file);
	std::cout << "Database saved : [" << this->getSize() << " account saved]"<< std::endl;
	this->am.unlockReader();
}

bool Database::contains(const int id) const {
	this->am.lockReader();
	for (const auto &user : this->data) {
		if (user.isId(id)) { return true; }
	} this->am.unlockReader(); return false;
}

bool Database::contains(const char username[32]) const {
	this->am.lockReader();
	for (const auto &user : this->data) {
		if (user.isUsername(username)) { return true; }
	} this->am.unlockReader(); return false;
}

User* Database::getUser(const int id) {
	this->am.lockReader();
	for (auto &user : this->data) {
		if (user.isId(id)) { this->am.unlockReader(); return &user; }
	} this->am.unlockReader(); return nullptr;
}

User* Database::getUser(const char username[32]) {
	this->am.lockReader();
	for (auto &user : this->data) {
		if (user.isUsername(username)) { this->am.unlockReader(); return &user; }
	} this->am.unlockReader(); return nullptr;
}

void Database::addUser(std::string username, std::string password) {
	User user{this->getSize()+1, username.c_str(), password.c_str()};
	this->am.lockWriter();
	this->data.push_back(user);
	this->am.unlockWriter();
}

void Database::print_in_file() {
	std::ofstream file("clear.txt", std::ios::out | std::ios::trunc);
	if (file) {
		for (auto &user : this->data) {file << user.toString() << std::endl;}
	}
	file.close();
}

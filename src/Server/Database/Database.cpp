#include "Database.hpp"

#include "User.hpp"

using std::fopen; using std::fclose;
using std::fread; using std::fwrite;
using std::cout; using std::endl;
using std::fseek; using std::ftell;

void Database::load() {
	this->am.lockWriter();
	FILE *file = fopen(path, "rb");
	if (!file) {data.reserve(10); cout << "Database empty !" << endl; return;}
	data.reserve(fileSize(file)/sizeof(User));
	User user;
	while (fread(&user, sizeof(User), 1, file)) data.push_back(user);
	fclose(file);
	cout << "Database loaded : [" << this->getSize() << " account registered]" << endl;
	this->am.unlockWriter();
}

size_t Database::fileSize(FILE *file) {
	// Save la position de debut du fichier de la db
	size_t cursor = ftell(file);
	// Envoie le curseur à la fin du fichier
	fseek(file, 0, SEEK_END);
	// Récupère la taille du fichier
	size_t size = std::ftell(file);
	// Remet le curseur au debut
	fseek(file, 0, cursor);
	return size;
}

void Database::save() {
	this->am.lockReader();
	FILE  *file = fopen(path, "w+");
	if (!file) exit(0);
	if (fwrite(data.data(), sizeof(User), data.size(), file) < 0) cout << "Database not saved" << endl;
	fclose(file);
	cout << "Database saved : [" << this->getSize() << " account saved]"<< endl;
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

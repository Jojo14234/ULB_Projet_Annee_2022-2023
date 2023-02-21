#include "Database.hpp"
#include "User.hpp"


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
	this->am.lockReader();
	FILE *file = std::fopen(path, "w+");
	if (!file) exit(0);
	size_t size = this->data.size();
	fwrite(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) this->data[i].write(file);
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

std::string Database::getUsername(const int id) { return this->getUser(id)->getUsername(); }

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

void bubble_sort(std::vector<User> &data) {
    for (unsigned i=0; i < data.size(); i++) {
        for (unsigned j=0; j < data.size() - i; j++) {
            if (data[j].getStats().getScore() > data[j+1].getStats().getScore()) {
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
	auto it = std::find(this->data.begin(), this->data.end(), user);
	this->data.erase(it);
}

bool Database::contains(const User &user) const { return this->contains(user.getId()); }
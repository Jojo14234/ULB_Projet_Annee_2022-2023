#include "FriendList.hpp"
#include "Database.hpp"
#include "User.hpp"

void FriendList::addFriend(int from, int id, Database& db) { 
	this->am.lockWriter();
	this->ids.push_back(id);
	db.getUser(id)->addFriend(from);
	this->am.unlockWriter();
}

void FriendList::addFriend(int id) {
	this->am.lockWriter();
	this->ids.push_back(id);
	this->am.unlockWriter();
}

void FriendList::removeFriend(int id) {
	this->am.lockWriter(); 
	auto it = std::find(this->ids.begin(), this->ids.end(), id);
	this->ids.erase(it); 
	this->am.unlockWriter();
}

void FriendList::removeFriend(int from, int id, Database& db) {
	this->am.lockWriter();
	auto it = std::find(this->ids.begin(), this->ids.end(), id);
	this->ids.erase(it);
	db.getUser(id)->removeFriend(from);
	this->am.unlockWriter();
}

std::string FriendList::toString(Database &db) const {
	std::string str = "Liste d'amis (" + std::to_string(this->getFriendsCount()) + "):\n";
	for (auto id : ids){
		str += ("✿ " + db.getUsername(id) + "\n");
	}
	return str;
}

void FriendList::write(FILE* file) {
	size_t size = this->ids.size();
	fwrite(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) {
		fwrite(&(this->ids[i]), sizeof(int), 1, file);
	}
}

void FriendList::read(FILE* file) {
	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	std::cout << size << std::endl;
	for (size_t i = 0; i < size; i++) {
		int x;
		fread(&x, sizeof(int), 1, file);
		this->ids.push_back(x);
	}
}


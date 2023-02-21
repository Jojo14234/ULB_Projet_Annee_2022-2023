#include "FriendList.hpp"
#include "Database.hpp"
#include "User.hpp"

void FriendList::addFriend(int current_user, int new_friend, Database& db) { 
	this->am.lockWriter();
	this->ids.push_back(new_friend);
	db.getUser(new_friend)->friend_list.ids.push_back(current_user);
	this->am.unlockWriter();
}

void FriendList::removeFriend(int current_user, int old_friend, Database& db) {
	this->am.lockWriter();
	auto it = std::find(this->ids.begin(), this->ids.end(), old_friend);
	this->ids.erase(it);
	std::vector<int>& other_friend_list = db.getUser(old_friend)->friend_list.ids;
	auto it2 = std::find(other_friend_list.begin(), other_friend_list.end(), current_user);
	other_friend_list.erase(it2); 
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
	for (size_t i = 0; i < size; i++) {
		int x;
		fread(&x, sizeof(int), 1, file);
		this->ids.push_back(x);
	}
}


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

std::string FriendList::toString(Database &db) const {
	std::string str = "Liste d'amis:\n\n";
	for (auto id : ids){
		str += ("• " + db.getUsername(id) + "\n");
	}
	return str;
}
#include "FriendRequestList.hpp"
#include "Database.hpp"
#include "User.hpp"

void FriendRequestList::sendRequest(int from, int to, Database& db) {
	this->am.lockWriter(); 
	this->sent.push_back(to);
	db.getUser(to)->receiveRequest(from);
	this->am.unlockWriter();
}

void FriendRequestList::receiveRequest(int id) { 
	this->am.lockWriter();
	this->received.push_back(id); 
	this->am.unlockWriter();
}

void FriendRequestList::removeRequest(int from, int to, Database& db) { 
	this->am.lockWriter();
	auto it = std::find(this->sent.begin(), this->sent.end(), to);
	this->sent.erase(it); 
	db.getUser(to)->removeRequest(from);
	this->am.unlockWriter();
}

void FriendRequestList::removeRequest(int id) { 
	this->am.lockWriter();
	auto it = std::find(this->received.begin(), this->received.end(), id);
	this->received.erase(it); 
	this->am.unlockWriter();
}

std::string FriendRequestList::toString(Database &db) const {
	std::string str = "Demandes d'ami en attente (%d):\n\n",getPendingFriendRequestsCount();
	for (auto id : received){
		str += ("• " + db.getUsername(id) + "\n");
	}
	return str;
}
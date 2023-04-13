#include "FriendRequestList.hpp"
#include "../Database.hpp"
#include "../User.hpp"

void FriendRequestList::sendRequest(int current_user, int receiver, Database& db) {
	this->am.lockWriter(); 
	this->sent.push_back(receiver);
	db.getUser(receiver)->friend_request_list.received.push_back(current_user);
	this->am.unlockWriter();
}

void FriendRequestList::removeRequest(int current_user, int sender, Database& db) { 
	this->am.lockWriter();
	auto it = std::find(this->received.begin(), this->received.end(), sender);
	this->received.erase(it); 
	std::vector<int>& other_sent = db.getUser(sender)->friend_request_list.sent;
	auto it2 = std::find(other_sent.begin(), other_sent.end(), current_user);
	other_sent.erase(it2); 
	this->am.unlockWriter();
}

std::string FriendRequestList::toString(Database &db) const {
	std::string str = "Demandes d'ami en attente (" + std::to_string(this->getPendingFriendRequestsCount()) + "):\n";
	for (auto id : received){
		str += ("■ " + db.getUsername(id) + "\n");
	}
	return str;
}

std::vector<std::string> FriendRequestList::toVector(Database &db) const {
	std::vector<std::string> vec;
	for (auto id : received){ vec.push_back(db.getUsername(id)); }
	return vec;
}

void FriendRequestList::write(FILE* file) {
	size_t size = this->received.size();
	fwrite(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) {
		fwrite(&(this->received[i]), sizeof(int), 1, file);
	}
	size = this->sent.size();
	fwrite(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) {
		fwrite(&(this->sent[i]), sizeof(int), 1, file);
	}
}

void FriendRequestList::read(FILE* file) {
	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) {
		int x;
		fread(&x, sizeof(int), 1, file);
		this->received.push_back(x);
	}
	fread(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; i++) {
		int x;
		fread(&x, sizeof(int), 1, file);
		this->sent.push_back(x);
	}
}

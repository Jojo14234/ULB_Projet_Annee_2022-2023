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
	auto it = std::find(this->received.begin(), this->received.end(), to);
	this->received.erase(it); 
	db.getUser(to)->removeRequest(from);
	this->am.unlockWriter();
}

void FriendRequestList::removeRequest(int id) { 
	this->am.lockWriter();
	auto it = std::find(this->sent.begin(), this->sent.end(), id);
	this->sent.erase(it); 
	this->am.unlockWriter();
}

void FriendRequestList::acceptRequest(int from, int to, Database& db) {
	this->am.lockWriter();
	auto it = std::find(this->received.begin(), this->received.end(), to);
	this->received.erase(it); 
	db.getUser(to)->removeSent(from);
	this->am.unlockWriter();
}

void FriendRequestList::acceptRequest(int id) {
	this->am.lockWriter();
	auto it = std::find(this->sent.begin(), this->sent.end(), id);
	this->sent.erase(it);
	this->am.unlockWriter();
}

std::string FriendRequestList::toString(Database &db) const {
	std::string str = "Demandes d'ami en attente (" + std::to_string(this->getPendingFriendRequestsCount()) + "):\n";
	for (auto id : received){
		str += ("■ " + db.getUsername(id) + "\n");
	}
	return str;
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

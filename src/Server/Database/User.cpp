#include "User.hpp"


User::operator std::string() {
	std::string str;
	str += "Username : ";
	str += this->getUsername();
	str += " | Password : ";
	str += this->getPassword();
	str += " | Id : ";
	str += std::to_string(this->getId());
	return str;
}


void User::sendRequest(int id, Database& db) {
	this->friend_request_list.sendRequest(this->getId(), id, db);
}

void User::removeRequest(int id, Database& db) {
	this->friend_request_list.removeRequest(this->getId(), id, db);
}

void User::acceptRequest(int id, Database& db) { 
	this->friend_request_list.removeRequest(this->getId(), id, db);
	this->friend_list.addFriend(this->getId(), id, db); 
}

void User::removeFriend(const int id, Database& db) {
	this->friend_list.removeFriend(this->getId(), id, db);
}


void User::write(FILE* file) {
	fwrite(&(this->id), sizeof(int), 1, file);
	fwrite(this->username, sizeof(char), 32, file);
	fwrite(this->password, sizeof(char), 64, file);
	this->stats.write(file);
	this->friend_list.write(file);
	this->friend_request_list.write(file);
}

void User::read(FILE* file) {
	fread(&(this->id), sizeof(int), 1, file);
	fread(this->username, sizeof(char), 32, file);
	fread(this->password, sizeof(char), 64, file);
	this->stats.read(file);
	this->friend_list.read(file);
	this->friend_request_list.read(file);
}

#ifndef _USER_HPP
#define _USER_HPP

#include <string>
#include <cstring>

#include "GameStats.hpp"
#include "Friend/FriendList.hpp"
#include "Friend/FriendRequestList.hpp"
#include "Chat/Chat.hpp"
#include "Database.hpp"


class User {

	int id;
	char username[32];
	char password[64];

	GameStats stats;
	FriendList friend_list;
	FriendRequestList friend_request_list;
	Chat chat;

public:

	friend class FriendList;
	friend class FriendRequestList;

	User()=default;
	User(int id, const char username[32], const char password[64]): id{id} {
		strcpy(this->username, username);
		strcpy(this->password, password);
	}

	// Write Read
	void write(FILE* file) {
		fwrite(&(this->id), sizeof(int), 1, file);
		fwrite(this->username, sizeof(char), 32, file);
		fwrite(this->password, sizeof(char), 64, file);
		this->stats.write(file);
		this->friend_list.write(file);
		this->friend_request_list.write(file);
	}

	void read(FILE* file) {
		fread(&(this->id), sizeof(int), 1, file);
		fread(this->username, sizeof(char), 32, file);
		fread(this->password, sizeof(char), 64, file);
		this->stats.read(file);
		this->friend_list.read(file);
		this->friend_request_list.read(file);
	}

	// To String
	std::string toString() {
		std::string user;
		user += "Username : ";
		user += this->getUsername();
		user += " | Password : ";
		user += this->getPassword();
		user += " | Id : ";
		user += std::to_string(this->getId());
		return user;
	}
	
	// To compare
	bool operator==(const User &other) const { return id == other.id; }

	// GETTERS
	int getId() const { return id; }
	const char* getUsername() const { return username; }
	const char* getPassword() const { return password; }
	const GameStats& getStats() const { return stats; }
	const FriendList& getFriendList() const { return friend_list; }
	const FriendRequestList& getFriendRequestList() const { return friend_request_list; }

	// CHECKER
	bool isId(const int id) const { return this->id == id; }
	bool isUsername(const char* username) const { return std::string(this->username) == username; }
	bool isPassword(const char* other) const { return std::string(this->password) == other; }

	bool isFriendWith(const User &other) const { return friend_list.contains(other.id); }
	bool isFriendWith(const int other_id) const { return friend_list.contains(other_id); }

	bool hasSentFriendRequestTo(const User &other) const { return friend_request_list.sentListContains(other.id); }
	bool hasSentFriendRequestTo(const int other_id) const { return friend_request_list.sentListContains(other_id); }
	
	bool hasReceiveFriendRequestFrom(const User &other) const { return friend_request_list.receivedListContains(other.id); }
	bool hasReceiveFriendRequestFrom(const int other_id) const { return friend_request_list.receivedListContains(other_id); }

	// MODIFIERS
	void updateStats(const GameStats &stats) { this->stats += stats; }
	
	// FRIEND INTERACTIONS
	void sendRequest(int id, Database& db) { this->friend_request_list.sendRequest(this->getId(), id, db); }
	void removeRequest(int id, Database& db) { this->friend_request_list.removeRequest(this->getId(), id, db); }
	
	void acceptRequest(int id, Database& db) { 
		this->friend_request_list.removeRequest(this->getId(), id, db);
		this->friend_list.addFriend(this->getId(), id, db); 
	}
	void removeFriend(const int id, Database& db) { this->friend_list.removeFriend(this->getId(), id, db); }
};


#endif

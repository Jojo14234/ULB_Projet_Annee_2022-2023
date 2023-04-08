#ifndef _SERVER_USER_HPP
#define _SERVER_USER_HPP

#include <string>
#include <cstring>

#include "GameStats.hpp"
#include "Friend/FriendList.hpp"
#include "Friend/FriendRequestList.hpp"
#include "Database.hpp"


class User {

	int id;
	char username[32];
	char password[64];

	GameStats stats;
	FriendList friend_list;
	FriendRequestList friend_request_list;

public:

	friend class FriendList;
	friend class FriendRequestList;

	User()=default;
	User(int id, const char username[32], const char password[64]): id{id} {
		strcpy(this->username, username);
		strcpy(this->password, password);
	}

	// To String
	operator std::string() { return std::string(this->username); }
	
	// To compare
	bool operator==(const User &other) const { return id == other.id; }

	// GETTERS
    int getId() const { return id; }
    const std::string getUsername() const {std::cout << (void*)username << std::endl; return std::string{username}; }
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
    void resetStats() { this->stats = GameStats{};}
	
	// FRIEND INTERACTIONS
	void sendRequest(int id, Database& db);
	void removeRequest(int id, Database& db);
	void acceptRequest(int id, Database& db);
	void removeFriend(const int id, Database& db);

	// WRITE READ
	void write(FILE* file);
	void read(FILE* file);

};

#endif
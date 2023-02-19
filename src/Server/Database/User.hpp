#ifndef _USER_HPP
#define _USER_HPP

#include <string>
#include <cstring>

#include "GameStats.hpp"
#include "FriendList.hpp"
#include "FriendRequestList.hpp"
#include "Database.hpp"

class User {

	int id;
	char username[32];
	char password[64];

	GameStats stats;
	FriendList friend_list;
	FriendRequestList friend_request_list;

public:

    User()=default;
	User(int id, const char username[32], const char password[64]): id{id} {
        strcpy(this->username, username);
        strcpy(this->password, password);
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

	// MODIFIERS
	void updateStats(const GameStats &stats) { this->stats += stats; }
	/*void addFriend(const int id) { this->friend_list.addFriend(id); }
	void addFriend(const User &other) { this->friend_list.addFriend(other.id); }
	void removeFriend(const int id) { this->friend_list.removeFriend(id); }
	void removeFriend(const User &other) { this->friend_list.removeFriend(other.id); }*/
	void sendRequest(int id, Database& db) { this->friend_request_list.sendRequest(this->getId(), id, db); }
	void removeRequest(int id, Database& db) { this->friend_request_list.removeRequest(this->getId(), id, db); }
	void receiveRequest(int id) { this->friend_request_list.receiveRequest(id); } //should be private
	void removeRequest(int id) { this->friend_request_list.removeRequest(id); } //should be private

	//void acceptRequest(int id)

};


#endif

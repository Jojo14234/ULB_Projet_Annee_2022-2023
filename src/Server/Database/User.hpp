#ifndef _USER_HPP
#define _USER_HPP

#include <string>
#include <cstring>

#include "GameStats.hpp"
#include "FriendList.hpp"
#include "FriendRequestList.hpp"


class User {

	int id;
	std::string username;
	std::string password;

	GameStats stats;
	FriendList friend_list;
	FriendRequestList friend_request_list;

	void addFriendRequest(const User &other) { this->friend_request_list.addRequest(other.getId()); }

public:

    User()=default;
	User(int id, const std::string username, const std::string password): id{id}, username{username}, password{password} {}

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
	const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
    const GameStats& getStats() const { return stats; }
	const FriendList& getFriendList() const { return friend_list; }
	const FriendRequestList& getFriendRequestList() const { return friend_request_list; }

	// CHECKER
	bool isId(const int id) const { return this->id == id; }
	bool isUsername(const char* username) const { return std::string(this->username) == username; }
	bool isPassword(const char* other) const { return std::string(this->password) == other; }

	bool isFriendWith(const User &other) const { return friend_list.contains(other.id); }
	bool isFriendWith(const int other_id) const { return friend_list.contains(other_id); }

	// MODIFIERS
	void updateStats(const GameStats &stats) { this->stats += stats; }
	void addFriend(const int id) { this->friend_list.addFriend(id); }
	void addFriend(const User &other) { this->friend_list.addFriend(other.id); }
	void removeFriend(const int id) { this->friend_list.removeFriend(id); }
	void removeFriend(const User &other) { this->friend_list.removeFriend(other.id); }
	void sendFriendRequest(User &other) { other.addFriendRequest(*this); }
	void removeFriendRequest(User &other) { other.}

};


#endif

#ifndef _SERVER_FRIEND_LIST_HPP
#define _SERVER_FRIEND_LIST_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "../../../Utils/AccessMonitor.hpp"
#include "../../../Utils/Config/Configs.hpp"


class Database;

class FriendList {
	
	AccessMonitor am;
	
	// List of ids of friends user
	std::vector<int> ids;

public:

	// Add a friend
	void addFriend(int current_user, int new_friend, Database& db);

	// Remove a friend
	void removeFriend(int current_user, int old_friend, Database& db);
	
	// If contains
	bool contains(int id) const { return std::find(this->ids.begin(), this->ids.end(), id) != this->ids.end(); }
	
	// GETTERS
	int getFriendsCount() const { return this->ids.size(); }

	std::string toString(Database &db) const;

	std::vector<std::string> toVector(Database &db) const;

	// WRITE READ
	void write(FILE* file);
	void read(FILE* file);
};


#endif

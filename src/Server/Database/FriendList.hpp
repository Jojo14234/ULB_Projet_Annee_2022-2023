#ifndef _FRIEND_LIST_HPP
#define _FRIEND_LIST_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "../../utils/AccessMonitor.hpp"

class Database;

class FriendList {
	
	AccessMonitor am;
	std::vector<int> ids;

public:

	FriendList()=default;

	// Add a friend
	void addFriend(int from, int id, Database& db);
	void addFriend(int id);

	// Remove a friend
	void removeFriend(int id);
	
	// If contains
	bool contains(int id) const { return std::find(this->ids.begin(), this->ids.end(), id) != this->ids.end(); }
	
	// GETTERS
	int getFriendsCount() const { return this->ids.size(); }

	std::string toString(Database &db) const;
};


#endif

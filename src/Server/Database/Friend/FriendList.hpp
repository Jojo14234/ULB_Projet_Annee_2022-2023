#ifndef _FRIEND_LIST_HPP
#define _FRIEND_LIST_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "../../../utils/AccessMonitor.hpp"
#include "../../../utils/Configs.hpp"


class Database;

class FriendList {
	
	AccessMonitor am;
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

	// Write Read
	void write(FILE* file);
	void read(FILE* file);

};


#endif
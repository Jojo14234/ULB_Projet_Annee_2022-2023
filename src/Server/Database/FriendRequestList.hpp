#ifndef _FRIEND_REQUEST_LIST_HPP
#define _FRIEND_REQUEST_LIST_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "../../utils/AccessMonitor.hpp"

class Database;

class FriendRequestList {
	
	AccessMonitor am;
	std::vector<int> received;
	std::vector<int> sent;

public:

	FriendRequestList() = default;

	// Send a friend request
	void sendRequest(int from, int to, Database& db);
	// receive a friend resquest
	void receiveRequest(int id);

	// Remove a friend
	void removeRequest(int from, int to, Database& db);

	void removeRequest(int id);
	
	// If contains
	bool contains(int id) const { return std::find(this->received.begin(), this->received.end(), id) != this->received.end(); }
	
	// GETTERS
	int getPendingFriendRequestsCount() const { return this->received.size(); }

	std::string toString(Database &db) const;
};


#endif

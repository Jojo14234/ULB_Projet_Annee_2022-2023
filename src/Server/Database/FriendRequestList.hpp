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
	void receiveRequest(int id);

	// Remove a friend
	void removeRequest(int from, int to, Database& db);
	void removeRequest(int id);

	void acceptRequest(int from, int to, Database& db);
	void acceptRequest(int id);
	
	// If contains
	bool sentListContains(int id) const { return std::find(this->sent.begin(), this->sent.end(), id) != this->sent.end(); }
	bool receivedListContains(int id) const { return std::find(this->received.begin(), this->received.end(), id) != this->received.end(); }

	// GETTERS
	int getPendingFriendRequestsCount() const { return this->received.size(); }

	std::string toString(Database &db) const;
};


#endif

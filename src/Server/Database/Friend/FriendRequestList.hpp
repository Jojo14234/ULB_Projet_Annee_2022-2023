#ifndef _SERVER_FRIEND_REQUEST_LIST_HPP
#define _SERVER_FRIEND_REQUEST_LIST_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "../../../Utils/AccessMonitor.hpp"
#include "../../../Utils/Config/Configs.hpp"


class Database;

class FriendRequestList {
	
	AccessMonitor am;

	// list of requests received
	std::vector<int> received;

	// List of requests sent
	std::vector<int> sent;

public:

	// Send a friend request
	void sendRequest(int current_user, int receiver, Database& db);

	// Remove a friend
	void removeRequest(int current_user, int sender, Database& db);
	
	// If contains
	bool sentListContains(int id) const { return std::find(this->sent.begin(), this->sent.end(), id) != this->sent.end(); }
	bool receivedListContains(int id) const { return std::find(this->received.begin(), this->received.end(), id) != this->received.end(); }

	// GETTERS
	int getPendingFriendRequestsCount() const { return this->received.size(); }

	std::string toString(Database &db) const;

	std::vector<std::string> toVector(Database &db) const;

	// WRITE READ
	void write(FILE* file);
	void read(FILE* file);
	
};


#endif

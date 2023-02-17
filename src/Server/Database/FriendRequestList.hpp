#ifndef _FRIEND_REQUEST_LIST_HPP
#define _FRIEND_REQUEST_LIST_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "Database.hpp"

class FriendRequestList {
	
	std::vector<int> sent;
	std::vector<int> received;

public:

	FriendRequestList() = default;

	// Add a friend
	void addRequest(int id) { this->sent.push_back(id); }
	// Remove a friend
	void removeRequest(int id) { 
		auto it = std::find(this->sent.begin(), this->sent.end(), id);
		this->sent.erase(it); 
	}
	
	// If contains
	bool contains(int id) const { return std::find(this->sent.begin(), this->sent.end(), id) != this->sent.end(); }
	
	// GETTERS
	int getFriendsCount() const { return this->sent.size(); }

	std::string toString(Database &db) const {
		std::string str = "Demandes d'ami en attente:\n\n";
		for (auto id : sent){
			str += ("• " + db.getUsername(id) + "\n");
		}
		return str;
	}
};


#endif

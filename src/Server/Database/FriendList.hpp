#ifndef _FRIEND_LIST_HPP
#define _FRIEND_LIST_HPP

#include <vector>
#include <algorithm>


class FriendList {
	
	std::vector<int> ids;

public:

	FriendList()=default;

	void addFriend(int id) { this->ids.push_back(id); }

	void removeFriend(int id) { 
		auto it = std::find(this->ids.begin(), this->ids.end(), id);
		this->ids.erase(it); 
	}

	bool contains(int id) const { return std::find(this->ids.begin(), this->ids.end(), id) != this->ids.end(); }

	int getFriendsCount() const { return this->ids.size(); }

};


#endif
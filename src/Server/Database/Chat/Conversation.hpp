#ifndef _CHAT_CONVERSATION_HPP
#define _CHAT_CONVERSATION_HPP

#include <vector>
#include <string>

//#include "../User.hpp"
#include "Message.hpp"

class User;

class Conversation {

	User* user1;
	User* user2;
	std::vector<Message> messages;

public:
	
	Conversation(User* user1, User* user2):user1{user1},user2{user2} {}
	
	bool isATalker(User* user) { return this->user1 == user or this->user2 == user; }

	operator std::string();

	void addMsg(User* sender, const std::string &msg);

};

#endif

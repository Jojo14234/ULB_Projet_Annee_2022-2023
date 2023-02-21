#ifndef _SERVER_CHAT_CONVERSATION_HPP
#define _SERVER_CHAT_CONVERSATION_HPP

#include <vector>
#include <string>

#include "Message.hpp"

class User;		// forward declaration

class Conversation {

	User* user1;
	User* user2;
	std::vector<Message> messages;

public:
	
	Conversation(User* user1, User* user2):user1{user1},user2{user2} {}
	
    // To convert the conversation to a string
	operator std::string();

	// To add a message to the conversation
	void addMsg(User* sender, const std::string &msg);

	// if is a talker of the conversation
	bool isATalker(User* user) { return this->user1 == user or this->user2 == user; }

};

#endif

#ifndef _SERVER_CHAT_CONVERSATION_HPP
#define _SERVER_CHAT_CONVERSATION_HPP

#include <vector>
#include <array>
#include <string>

#include "Message.hpp"

class User;		// forward declaration

class Conversation {

	// Talkers
	std::array<User*, 2> users;
	
	// List of messages
	std::vector<Message> messages;

public:
	
	Conversation(User* user1, User* user2):users{user1, user2} {}
	
    // To convert the conversation to a string
	operator std::string();

	// To add a message to the conversation
	void addMsg(User* sender, const std::string &msg);

	// if is a talker of the conversation
	bool isATalker(User* user) { return this->users[0] == user or this->users[1] == user; }

};

#endif
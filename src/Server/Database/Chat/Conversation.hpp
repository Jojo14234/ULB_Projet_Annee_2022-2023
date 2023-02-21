#ifndef _CHAT_CONVERSATION_HPP
#define _CHAT_CONVERSATION_HPP

#include <vector>
#include <string>

#include "Message.hpp"


class Conversation {

	int receiver;
	std::vector<Message> messages;

public:
	
	Conversation(int receiver):receiver{receiver} {}
	
	operator std::string();

	void addMsg(Message &msg);

	
};

#endif

#include "Conversation.hpp"
#include "Message.hpp"


Conversation::operator std::string() {
	return "";
}

void Conversation::addMsg(User* sender, const std::string &msg) {
	this->messages.emplace_back(sender, msg.c_str());
}

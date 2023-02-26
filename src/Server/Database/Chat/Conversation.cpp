#include "Conversation.hpp"
#include "Message.hpp"


Conversation::operator std::string() {
	std::string output;
	for (auto& message : messages) {
        output += std::string{message} + "\n";
    }
	return output;
}

void Conversation::addMsg(User* sender, const std::string &msg) {
	this->messages.emplace_back(sender, msg.c_str());
}

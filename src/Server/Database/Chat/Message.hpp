#ifndef _CHAT_MESSAGE_HPP
#define _CHAT_MESSAGE_HPP

#include <vector>
#include <string>
#include <cstring>

//#include "../User.hpp"

class User;

class Message {

	User* writer;
	char msg[1024];

public:

	Message(User* writer, const char msg[1024]):writer{writer} { strcpy(this->msg, msg); }

	operator std::string() { return ""; }

};

#endif

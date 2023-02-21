#ifndef _CHAT_MESSAGE_HPP
#define _USER_MESSAGE_HPP

#include <vector>
#include <string>
#include <cstring>


class Message {

	int writer;
	int receiver;
	char msg[1024];

public:

	Message(int writer, int receiver, char msg[1024]):writer{writer},receiver{receiver} { strcpy(this->msg, msg); }

	operator std::string();

};

#endif

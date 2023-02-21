#ifndef _USER_CHAT_HPP
#define _USER_CHAT_HPP

#include <vector>

#include "Conversation.hpp"


class Chat {

	std::vector<Conversation> convs;

public:

	void createConv(int id);
	void removeConv(int id);

};

#endif

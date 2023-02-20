#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include "../utils/Configs.hpp"


class Capitalist {

public:

	Capitalist()=default;

	void receiveQuery(GAME_QUERY_TYPE query) { std::cout << "capitalist : " << (int)query << std::endl; }

	void sendMessage(std::string &output) { output = "coucou ici capitalist"; }

};

#endif
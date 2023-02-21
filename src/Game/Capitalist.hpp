#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>

#include "../utils/Configs.hpp"


class Capitalist {

public:

	Capitalist()=default;

	void receiveQuery(GAME_QUERY_TYPE query, sf::Packet &packet) {
		std::string s1="", s2="";
		switch (query) {
			case GAME_QUERY_TYPE::ARG1 : packet >> s1; break;
			case GAME_QUERY_TYPE::ARG2 : packet >> s1 >> s2; break;
			default : break;
		}
		std::cout << "in capitalist : " << (int)query << " " << s1 << " " << s2 << std::endl;
	}

	void sendMessage(std::string &output) { output = "coucou ici capitalist"; }

};

#endif
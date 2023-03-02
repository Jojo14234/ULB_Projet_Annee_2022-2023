#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"

class Player;

class Company : public Land {

	int getRentPrice(); //dé  jeter les dés x5 ou x12 selon le owner possession
	
public:

	void action(Player* player);

};

#endif
#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"
#include "../../../../../Game/Dice.hpp"

class Player;

class Company : public Land {

	int getRentPrice();
	
public:

	void playerPurchase(Player* player);

};

#endif
#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"
#include "../../../../../Game/Dice.hpp"

class Player;

class Company : public Land {
public:
    int getRentPrice();
    using Land::Land;
	void playerPurchase(Player* player);

};

#endif
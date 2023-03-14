#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"
#include "../../../../Dice/Dice.hpp"

class Player;

class Company : public Land {
public:

    using Land::Land;

    int getRentPrice() override ;

	void playerPurchase(Player* player) override ;

};

#endif
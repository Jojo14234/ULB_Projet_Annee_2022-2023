#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

#include "Land.hpp"

class Player;

class Station : public Land {

public:
    int getRentPrice() override ;
    using Land::Land;
	void playerPurchase(Player* player) override ;
};

#endif
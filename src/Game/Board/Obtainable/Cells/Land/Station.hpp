#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

#include "Land.hpp"

class PLayer;

class Station : public Land {

public:
    int getRentPrice();
    using Land::Land;
	void playerPurchase(Player* player);

};

#endif
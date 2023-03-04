#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

#include "Land.hpp"

class PLayer;

class Station : public Land {

	int getRentPrice();

public: 
	void playerPurchase(Player* player);

};

#endif
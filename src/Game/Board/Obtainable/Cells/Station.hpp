#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

#include "Land.hpp"

class PLayer;

class Station : public Land {

	int getRentPrice(); 
	// dépend de owner et le nombre de gare qu'il a

public:

	void action(Player* player);

};

#endif
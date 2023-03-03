#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

#include "Land.hpp"

class PLayer;

class Station : public Land {

	int getRentPrice() {
		unsigned int nbr_of_station = this->owner->getNumberOfStations();
		switch (nbr_of_station) {
			case 1:
				return 25;
			case 2:
				return 50;
			case 3:
				return 100;
			case 4:
				return 200;
		}
	}; 
	// dépend de owner et le nombre de gare qu'il a

public: 
	void action(Player* player);

	void playerPurchase(Player* player) {
		Land::acquireStation(player);
		//update dans les vecteurs de player
	}

};

#endif
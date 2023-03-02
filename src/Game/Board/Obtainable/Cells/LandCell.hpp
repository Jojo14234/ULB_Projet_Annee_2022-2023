#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "Land.hpp"


class PLayer;

class LandCell : public Cell {

    Land land;
    
	bool isOwner(Player* player) {return land->getOwner()==player;};

public: 

	LandCell(int pos, Land land): Cell{pos}, Land{land} {}
    
	void action(Player* player) {
		if (not this->isOwner(player) && owner != nullptr) {
			rent = land.getRentPrice();
			player->pay(rent, true);
			player->getClient()->send("Vous êtes tomber sur la propriéte"+land.getName());
			player->getClient()->send("Vous payer "+ std::toString(rent) + " euro de loyer");
		}
		else{
			player->getClient()->send("Vous êtes sur votre propriété "+land.getName())
		}
	};
};

#endif

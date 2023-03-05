#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "Land/Land.hpp"


class PLayer;

class LandCell : public Cell {

    Land* land;
    
	bool isOwner(Player* player) {return land->getOwner()==player;}

public: 

	LandCell(int pos, Land* land): Cell{pos}, land{land} {}
    
	void action(Player* player);

    Land* getLand(){return land;}

};

#endif

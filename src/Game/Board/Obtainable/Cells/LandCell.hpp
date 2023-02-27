#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "Land.hpp"


class PLayer;

class LandCell : public Cell {

    Land land;
    
	bool isOwner();

public: 

	LandCell(int pos, Land land): Cell{pos}, Land{land} {}
    
	void action(Player* player);

};

#endif

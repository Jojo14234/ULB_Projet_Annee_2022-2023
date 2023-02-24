#ifndef _GAME_CELL_HPP
#define _GAME_CELL_HPP

#include "../../../Player.hpp"
#include "Property.hpp"


class Cell {

    int position;

public:

	Cell(int pos): position{pos} {};
    
	virtual void action(Player* player)=0;

};

#endif

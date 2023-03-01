#ifndef _GAME_CELL_HPP
#define _GAME_CELL_HPP

#include "../Obtainable.hpp"
#include "Property.hpp"


class Player;

class Cell: public Obtainable {

    int position;

public:

	Cell(int pos): position{pos} {};
    
	virtual ~Cell()=default;

	virtual void action(Player* player)=0;

    int getPosition() { return position; }

};

#endif

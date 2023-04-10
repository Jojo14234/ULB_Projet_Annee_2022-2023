#ifndef _GAME_START_CELL_HPP
#define _GAME_START_CELL_HPP

#include <string>
#include "Cell.hpp"


class Player;

class StartCell: public Cell {

public:
    
	using Cell::Cell;
    
	void action(Player* player) override ;

};

#endif
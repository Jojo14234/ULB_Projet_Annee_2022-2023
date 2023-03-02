#ifndef _GAME_PARKING_CELL_HPP
#define _GAME_PARKING_CELL_HPP

#include "Cell.hpp"


class PLayer;

class ParkingCell : public Cell {

public:
	
	using Cell::Cell;
	
	void action(Player* player) {}

};

#endif
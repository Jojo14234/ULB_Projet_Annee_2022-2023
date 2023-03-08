#ifndef _GAME_PARKING_CELL_HPP
#define _GAME_PARKING_CELL_HPP

#include "Cell.hpp"


class PLayer;

class ParkingCell : public Cell {

public:
	
	using Cell::Cell;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
	void action(Player* player) override {}
#pragma GCC diagnostic pop

};

#endif
#ifndef _GAME_PARKING_CELL_HPP
#define _GAME_PARKING_CELL_HPP

#include "Cell.hpp"
#include "../../Player.hpp"

class ParkingCell : public{
public:
	using Cell::Cell;
	void action(Player* player) {};
}

#endif
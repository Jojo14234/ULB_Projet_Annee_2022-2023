#ifndef _GAME_LAND_HPP
#define _GAME_LAND_HPP

#include <string>
#include "../../../Player.hpp"

enum class CELL_STATUS {PAID, FREE, HYPOTEK};

class Land {
	Player* owner;
	std::string name;
	int purchase_price;

	CELL_STATUS status = CELL_STATUS::FREE;
	virtual getRentPrice();=0

public: 
	Land(Json::Value info) name{info["name"].asString()},
	purchase_price{info["purchase price"].asInt()} {}

}

#endif

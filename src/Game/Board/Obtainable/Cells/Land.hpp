#ifndef _GAME_LAND_HPP
#define _GAME_LAND_HPP

#include <string>


class PLayer;

enum class CELL_STATUS {PAID, FREE, HYPOTEK};

class Land {

protected:
	
	Player* owner;
	std::string name;
	int purchase_price;

	CELL_STATUS status = CELL_STATUS::FREE;
	int virtual getRentPrice()=0;

public: 

	Land(Json::Value info) : name{info["name"].asString()}, purchase_price{info["purchase price"].asInt()} {}

};

#endif

#ifndef _GAME_LAND_HPP
#define _GAME_LAND_HPP


#include <json/json.h>
#include <string>

enum class CELL_STATUS {PAID, FREE, HYPOTEK};
class Player;


class Land {

protected:
	
	Player* owner = nullptr;
	std::string name;
	int purchase_price;

	CELL_STATUS status = CELL_STATUS::FREE;
	int virtual getRentPrice()=0;

public: 

	Land(Json::Value info) : name{info["name"].asString()}, purchase_price{info["purchase price"].asInt()} {}
	Player* getOwner() {return this->owner;}
	std::string getName() {return name;}
	int getPurchasePrice() { return this->purchase_price;}

	virtual void playerPurchase(Player* player);

};

#endif

#ifndef _GAME_LAND_HPP
#define _GAME_LAND_HPP

#include <string>


class Player;

enum class CELL_STATUS {PAID, FREE, HYPOTEK};

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
	//void setOwner(Player* new_owner) {this->owner = new_owner;}
	std::string getName() {return name;}
	int getPurchasePrice() { return this->purchase_price;}

	virtual void playerPurchase(Player* player) {
		player->pay(purchase_price);
		this->owner = player;
	}

};

#endif

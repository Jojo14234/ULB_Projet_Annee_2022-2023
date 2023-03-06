#ifndef _GAME_LAND_HPP
#define _GAME_LAND_HPP


#include <json/json.h>
#include <string>
#include <iostream>

enum class LAND_STATUS {PAID, FREE, HYPOTEK};

class Player;


class Land {


protected:

    Player* owner = nullptr;

	std::string name;
	int purchase_price;
    int pos;

	LAND_STATUS status = LAND_STATUS::FREE;


public: 

	Land(Json::Value info) : name{info["name"].asString()}, purchase_price{info["purchase price"].asInt()}, pos{info["pos"].asInt()} {std::cout<<"Land constructor (owner) : "<< owner << std::endl;}
    
	virtual ~Land()=default;

	int virtual getRentPrice()=0;
	Player* getOwner() {std::cout << "Pointer to owner : " << owner << std::endl; return owner;} //TODO change
    void setOwner(Player* player) {owner = player; std::cout << "Owner was changed" << std::endl;}
	std::string getName() {return name;}
	int getPurchasePrice() { return this->purchase_price;}
	LAND_STATUS getStatus() {return status;}

	virtual void playerPurchase(Player* player);

	void mortgage(Player* player);
    void liftMortgage(Player* player);

};

#endif

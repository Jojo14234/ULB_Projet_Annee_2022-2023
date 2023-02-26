#ifndef _GAME_PROPERTY_HPP
#define _GAME_PROPERTY_HPP

#include <string>
#include <array>
#include <json/json.h>


class Player;

enum class COLOR {BROWN=1, LIGHT_BLUE=2, PINK=3, ORANGE=4, RED=5, YELLOW=6, GREEN=7, DARK_BLUE=8};
enum class CELL_STATUS {PAID, FREE, HYPOTEK};
enum class PROPERTY_LEVEL {EMPTY=0, ONE=1, TWO=2, THREE=3, FOUR=4, HOTEL=5};


class Property {

	std::string name;
    
	COLOR color;
    
	std::array<int, 6> rent_prices;
	int purchase_price;
	int construct_price;
    
	CELL_STATUS status = CELL_STATUS::FREE;
	PROPERTY_LEVEL level = PROPERTY_LEVEL::EMPTY;
    
	Player* owner;
	

	int getRentPrice() { return this->rent_prices[static_cast<int>(this->level)]; }

    void purchase();
    
	void rent();
    
	void setLevel();

public:
    
	Property(Json::Value prop_info): name{prop_info["name"].asString()}, color{static_cast<COLOR>(prop_info["color"].asInt())}, purchase_price{prop_info["purchase price"].asInt()}, construct_price{prop_info["construct price"].asInt()}{
		for (int i = 0; i<6; i++) this->rent_prices[i] = prop_info["rent prices"][i].asInt();
	}
    
	void action(Player* player);

};

#endif

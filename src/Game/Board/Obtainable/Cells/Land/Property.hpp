#ifndef _GAME_PROPERTY_HPP
#define _GAME_PROPERTY_HPP

#include <string>
#include <array>
#include <json/json.h>
#include "../../../../../utils/Configs.hpp"

#include "Land.hpp"


class Player;

enum class PROPERTY_LEVEL {EMPTY=0, ONE=1, TWO=2, THREE=3, FOUR=4, HOTEL=5};


class Property : Land {
    
	PROPERTY_COLOR color;
    
	std::array<int, 6> rent_prices;
	int construct_price;
    
	PROPERTY_LEVEL level = PROPERTY_LEVEL::EMPTY;

	int getRentPrice() { return this->rent_prices[static_cast<int>(this->level)]; }

    void purchase();
    
	void rent();
    
	void setLevel();

public:
    
	Property(Json::Value prop_info):  Land{prop_info}, color{static_cast<PROPERTY_COLOR>(prop_info["color"].asInt())},  construct_price{prop_info["construct price"].asInt()}{
		for (int i = 0; i<6; i++) this->rent_prices[i] = prop_info["rent prices"][i].asInt();
	}

	void playerPurchase(Player* player);

	int getLevel() { return static_cast<int>(level); }

};

#endif

#ifndef _GAME_PROPERTY_HPP
#define _GAME_PROPERTY_HPP

#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

#include <string>
#include <array>
#include "../../../../../utils/Configs.hpp"
#include "Land.hpp"


class Player;

enum class PROPERTY_LEVEL {EMPTY=0, ONE=1, TWO=2, THREE=3, FOUR=4, HOTEL=5};


class Property : public Land {
    
	PROPERTY_COLOR color;
    
	std::array<int, 6> rent_prices;
	int construct_price;
    
	PROPERTY_LEVEL level = PROPERTY_LEVEL::EMPTY;

	int getRentPrice() override {
        //hasAllColor
        return this->rent_prices[static_cast<int>(this->level)];
    }
    
	void levelUp() { int actual=static_cast<int>(this->level); this->level = static_cast<PROPERTY_LEVEL>(actual+1);}

    void levelDown() { int actual=static_cast<int>(this->level); this->level = static_cast<PROPERTY_LEVEL>(actual-1);}

    PROPERTY_COLOR getColor() { return this->color; }

    bool checkTransaction(Player* player, bool is_building);

    std::vector<Property*> getSameColorBuilding(std::vector<Property*> player_props);

    bool hasGoodLevel(int potential_level, std::vector<Property*> same_color);



public:
    
	Property(Json::Value prop_info):  Land{prop_info}, color{static_cast<PROPERTY_COLOR>(prop_info["color"].asInt())},  construct_price{prop_info["construct price"].asInt()}{
		for (int i = 0; i<6; i++) this->rent_prices[i] = prop_info["rent prices"][i].asInt();
	}

	void playerPurchase(Player* player) override ;

	int getIntLevel() { return static_cast<int>(level); }

    PROPERTY_LEVEL getLevel() {return this->level;}

    bool build(Player* player);

    bool sellBuilding(Player* player);

};

#endif

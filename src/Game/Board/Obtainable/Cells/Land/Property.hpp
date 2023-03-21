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

/*
 * Enum classe contenant les différents niveaux de construction d'une propriété.
 */
enum class PROPERTY_LEVEL {
    EMPTY,
    ONE,
    TWO,
    THREE,
    FOUR,
    HOTEL
};


class Property : public Land {
    
	PROPERTY_COLOR color;
    
	std::array<int, 6> rent_prices;
	int construct_price;
    
	PROPERTY_LEVEL level = PROPERTY_LEVEL::EMPTY;

public:
    
	Property(Json::Value prop_info)
        :Land{prop_info}, color{static_cast<PROPERTY_COLOR>(prop_info["color"].asInt())}, construct_price{prop_info["construct price"].asInt()}
        { for (int i = 0; i<6; i++) this->rent_prices[i] = prop_info["rent prices"][i].asInt(); }

	void playerPurchase(Player* player) override ;
    std::vector<Property*> getOtherSameColorPropFromPlayer(Player* player);
    bool hasAllSameColorProperties(Player* player);
    bool AllSameColorPropertiesHaveGoodLevel(Player* player, bool sell = false);
    bool build(Player* player);
    bool sellBuilding(Player* player);
    int getRentPrice() override;
    void levelUp();
    void levelDown();
    int getIntLevel() { return static_cast<int>(level); }
    PROPERTY_LEVEL getLevel() { return this->level; }
    PROPERTY_COLOR getColor() { return this->color; }

	bool isBuildable(Player* player);
	bool canSellBuilding(Player* player);

    void reset() {
        this->Land::reset();
        this->level = PROPERTY_LEVEL::EMPTY;
    }

    int getConstructPrice() { return this->construct_price; }


	////////////////////////

};

#endif

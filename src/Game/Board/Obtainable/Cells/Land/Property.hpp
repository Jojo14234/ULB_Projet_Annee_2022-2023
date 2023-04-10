#ifndef _GAME_PROPERTY_HPP
#define _GAME_PROPERTY_HPP


#include <string>
#include <array>
#include "Land.hpp"
#include "../../../../../utils/Configs.hpp"


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
    int construct_price;

	std::array<int, 6> rent_prices;
	PROPERTY_LEVEL level = PROPERTY_LEVEL::EMPTY;

public:

    Property(std::string name, int purchase_price, int pos, PROPERTY_COLOR color, int construct_price, std::array<int, 6> rent_prices)
            : Land{name, purchase_price, pos}, color{color}, construct_price{construct_price}, rent_prices{rent_prices} {};

    virtual ~Property()=default;

    // Getter
    int getRentPrice() override;
    int getIntLevel() const;
    int getConstructPrice() const;
    PROPERTY_LEVEL getLevel() const;
    PROPERTY_COLOR getColor() const;
    std::vector<Property*> getOtherSameColorPropFromPlayer(Player* player);

    // Setter

    // Check
    bool isBuildable(Player* player);
    bool canSellBuilding(Player* player);
    bool hasAllSameColorProperties(Player* player);
    bool AllSameColorPropertiesHaveGoodLevel(Player* player, bool sell = false);
    bool isMortgageable(Player* player);
    bool AllSameColorPropertiesHaveNoBuilding(Player* player);

    // Operation
    bool playerPurchase(Player* player) override;
    bool build(Player* player);
    bool build(Player* player, bool is_fast_game);
    bool sellBuilding(Player* player);
    void levelUp();
    void levelDown();
    int getIntLevel() { return static_cast<int>(level); }
    PROPERTY_LEVEL getLevel() { return this->level; }
    PROPERTY_COLOR getColor() { return this->color; }

	bool isBuildable(Player* player, bool is_fast_game);

    void reset();

    int getConstructPrice() { return this->construct_price; }


	////////////////////////

};

#endif

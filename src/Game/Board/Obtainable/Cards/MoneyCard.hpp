#ifndef _GAME_MONEY_CARD_HPP
#define _GAME_MONEY_CARD_HPP

#include <string>
#include "Card.hpp"
#include "../../../Player/Player.hpp"


class MoneyCard2 : public Card {

    int amount;

public:

    MoneyCard2(std::string description, int amount): Card{description}, amount{amount} {}

    int getAmount();
    void setAmount(int new_amount);

    void action(Player* player) override ;

};

class HouseHotelMoneyCard : public MoneyCard2 {
    int house_price;
    int hotel_price;

public:

    HouseHotelMoneyCard(std::string description, int amount ,int house_price, int hotel_price)
            : MoneyCard2{description, amount}, house_price{house_price}, hotel_price{hotel_price} {};

    void action(Player* player);

};

class ChoiceMoneyCard: public MoneyCard2 {

    std::string deck_name;

public:
    ChoiceMoneyCard(std::string description, int amount, std::string deck_name)
            :MoneyCard2{description, amount}, deck_name{deck_name} {}

    void action(Player* player);

};

class FromOtherMoneyCard: public MoneyCard2 {

public:
    FromOtherMoneyCard(std::string description, int amount)
            :MoneyCard2{description, amount} {};

    void action(Player* player);

};

#endif

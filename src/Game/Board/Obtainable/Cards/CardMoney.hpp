#ifndef _GAME_CARD_MONEY_HPP
#define _GAME_CARD_MONEY_HPP

#include <string>
#include <json/json.h>

#include "Card.hpp"
#include "../Player.hpp"


class CardMoney: public Card {

private:

	int amount;
	int amount_house;
	int amount_hotel;

public:
		
	explicit CardMoney(Json::Value &info):Card{info}, amount{info["amount"].asInt()}, amount_house{info["amount_house"].asInt()}, amount_hotel{info["amount_hotel"].asInt()} {}

	void action(Player* player);

};

#endif

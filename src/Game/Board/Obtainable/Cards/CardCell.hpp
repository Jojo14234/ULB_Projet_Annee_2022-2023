#ifndef _GAME_CARD_CELL_HPP
#define _GAME_CARD_CELL_HPP

#include <string>
#include <json/json.h>

#include "Card.hpp"


class CardCell: public Card {

private:

	int dest;
	bool gain_money;

public:

	explicit CardCell(Json::Value &info):Card{info}, dest{info["dest"].asInt()}, gain_money{info["dest"].asBool()} {}

	virtual void action(Player* player);

};

#endif

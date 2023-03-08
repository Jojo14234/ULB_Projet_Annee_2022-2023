#ifndef _GAME_CARD_CELL_HPP
#define _GAME_CARD_CELL_HPP

#include <string>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

#include "Card.hpp"


class Player;

class CellCard: public Card {

private:

	int dest;
	bool gain_money;	//"Si vous passez par la case départ, recevez 200$"

public:

	explicit CellCard(Json::Value &info):Card{info}, dest{info["dest"].asInt()}, gain_money{info["dest"].asBool()} {}

	void action(Player* player) override ;


											//déplace le joueur à cells[dest]
											// if gain money, check si position du joueur>dest (passe par case départ) pour argent

};

#endif

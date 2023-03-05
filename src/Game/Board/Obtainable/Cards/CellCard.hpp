#ifndef _GAME_CARD_CELL_HPP
#define _GAME_CARD_CELL_HPP

#include <string>
#include <json/json.h>

#include "Card.hpp"


class Player;

class CellCard: public Card {

private:

	int dest;
	bool gain_money;	//"Si vous passez par la case départ, recevez 200$"

public:

	explicit CellCard(Json::Value &info):Card{info}, dest{info["dest"].asInt()}, gain_money{info["dest"].asBool()} {}

	virtual void action(Player* player); /*{
		player->getClient()->send("Vous vous déplacez à la case "+ std::to_string(dest));
		player->move(player->getClient()->getGameServer()->getGame()->getBoard()->getCellByIndex(dest), gain_money);	//get cell by index
	};
    */


											//déplace le joueur à cells[dest]
											// if gain money, check si position du joueur>dest (passe par case départ) pour argent

};

#endif

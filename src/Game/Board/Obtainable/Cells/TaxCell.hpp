#ifndef _GAME_TAX_CELL_HPP
#define _GAME_TAX_CELL_HPP

#include <string>
#include <json/json.h>

#include "Cell.hpp"


class Player;


class TaxCell: public Cell {
    
	int tax_price;
	std::string name;


public:
    
	TaxCell(Json::Value info): Cell{info["pos"].asInt()}, tax_price{info["amount"].asInt()}, name{info["type"].asString()} {}
    
	void action(Player* player) {player->pay(tax_price, true); player->getClient()->send("Tu dois payer la taxe "+name+" et tu as payé "+std::to_string(tax_price)+" euro"}


};

#endif

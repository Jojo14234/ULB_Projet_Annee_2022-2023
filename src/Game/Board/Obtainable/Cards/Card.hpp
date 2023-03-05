#ifndef _GAME_CARD_HPP
#define _GAME_CARD_HPP

#include <string>
#include <json/json.h>

#include "../Obtainable.hpp"
/*
#include "../Cells/Land/Land.hpp"
#include "../Cells/Land/Property.hpp"
#include "../Cells/Land/Company.hpp"
#include "../Cells/Land/Station.hpp"
*/

class Player;

class Card: public Obtainable {

protected:

	std::string description;

public:

	explicit Card(Json::Value &info):description{info["descript"].asString()} {}

	virtual ~Card()=default;

	virtual void action(Player* player)=0;

	std::string getDesciption() { return description; }

};

#endif
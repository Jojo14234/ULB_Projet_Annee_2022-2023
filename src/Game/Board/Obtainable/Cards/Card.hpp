#ifndef _GAME_CARD_HPP
#define _GAME_CARD_HPP

#include <string>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

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

	virtual void action(Player* player) override =0;

	std::string getDescription() { return description; }

};

#endif
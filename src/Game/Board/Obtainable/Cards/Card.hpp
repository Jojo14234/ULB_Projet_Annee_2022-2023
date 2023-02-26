#ifndef _GAME_CARD_HPP
#define _GAME_CARD_HPP

#include <string>
#include <json/json.h>

#include "../Obtainable.hpp"


class Player;

class Card: public Obtainable {

protected:

	std::string description;

public:

	explicit Card(Json::Value &info):description{info["descript"].asString()} {}

	virtual ~Card();

	virtual void action(Player* player)=0;

};

#endif

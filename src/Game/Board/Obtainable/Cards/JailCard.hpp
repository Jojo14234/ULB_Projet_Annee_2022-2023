#ifndef _GAME_CARD_JAIL_HPP
#define _GAME_CARD_JAIL_HPP

#include <string>
#include <json/json.h>

#include "Card.hpp"


class Player;

class JailCard: public Card {

public:

	void action(Player* player);

};

#endif
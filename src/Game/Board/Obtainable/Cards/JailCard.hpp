#ifndef _GAME_CARD_JAIL_HPP
#define _GAME_CARD_JAIL_HPP

#include <string>
#include <json/json.h>

#include "Card.hpp"
#include "../../../Player.hpp"


class JailCard: public Card {

private:
	Player* owner;	//est à nullptr si est dans le deck


public:

	void action(Player* player);	//le player qui tire cette carte devient le owner
									//il peut utiliser la carte (sortir prison ou vente) et perds cette carte

};

#endif

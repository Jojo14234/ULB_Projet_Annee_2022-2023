#ifndef _GAME_CARD_JAIL_HPP
#define _GAME_CARD_JAIL_HPP

#include <string>
#include <jsoncpp/json/json.h>

#include "Card.hpp"


class Player;

class JailCard: public Card {

private:
	Player* owner;	//est à nullptr si est dans le deck


public:

	using Card::Card;

	void action(Player* player);	//le player qui tire cette carte devient le owner
									//si elle est re tiré mais qu'elle a deja un owner, re tiré une autre carte
									//il peut utiliser la carte (sortir prison ou vente) et perds cette carte

};

#endif

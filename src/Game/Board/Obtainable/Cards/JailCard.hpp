#ifndef _GAME_CARD_JAIL_HPP
#define _GAME_CARD_JAIL_HPP

#include <string>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

#include "Card.hpp"


class Player;

class JailCard: public Card {

	Player* owner=nullptr;	//est à nullptr si est dans le deck

public:

	using Card::Card;

	void action(Player* player) override;

	Player* getOwner() {return owner; }

	void setOwner(Player* new_player) { this->owner = new_player; }

                                    //le player qui tire cette carte devient le owner
									//si elle est re tiré mais qu'elle a deja un owner, re tiré une autre carte
									//il peut utiliser la carte (sortir prison ou vente) et perds cette carte

};

#endif

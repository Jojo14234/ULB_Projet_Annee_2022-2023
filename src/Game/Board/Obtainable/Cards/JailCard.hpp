#ifndef _GAME_CARD_JAIL_HPP
#define _GAME_CARD_JAIL_HPP

#include <string>
#include "Card.hpp"


class Player;

class JailCard: public Card {

	Player* owner = nullptr;

public:

	using Card::Card;

	Player* getOwner() { return owner; }
	void setOwner(Player* new_player) { this->owner = new_player; }

    void use();
    void action(Player* player) override;

};

#endif

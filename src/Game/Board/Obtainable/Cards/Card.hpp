#ifndef _GAME_CARD_HPP
#define _GAME_CARD_HPP


#include <string>
#include "../Obtainable.hpp"

class Player;

class Card: public Obtainable {

protected:

	std::string description;

public:

	Card(std::string description): description{description} {}

	virtual ~Card()=default;

	virtual void action(Player* player) override=0;

	std::string getDescription() { return description; }

};

#endif
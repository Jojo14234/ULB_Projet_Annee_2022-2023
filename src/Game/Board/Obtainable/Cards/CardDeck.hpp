#ifndef _GAME_CARD_DECK_HPP
#define _GAME_CARD_DECK_HPP

#include <string>
#include <json/json.h>
#include <array>
#include <memory>
#include <fstream>


#include "Card.hpp"
#include "MoneyCard.hpp"
#include "CellCard.hpp"


class CardDeck {
	
	std::array<std::shared_ptr<Card>, 16> card_list; // + ajouter carte prison

public:

	CardDeck()=default;

	CardDeck(std::string name);

	Card* drawACard();

};

#endif

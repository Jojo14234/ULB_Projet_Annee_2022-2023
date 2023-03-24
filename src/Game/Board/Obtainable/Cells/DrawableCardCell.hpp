#ifndef _GAME_DRAWABLE_CARD_CELL_HPP
#define _GAME_DRAWABLE_CARD_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "../Cards/CardDeck.hpp"


class Player;

class DrawableCardCell: public Cell {

    std::shared_ptr<CardDeck> deck;
    
	void drawACard();

public:

	DrawableCardCell(int pos, std::shared_ptr<CardDeck> one_deck, std::string name="Undefined")
            :Cell{pos, name}, deck{one_deck} {}

	void action(Player* player) override ; 

};

#endif

#ifndef _GAME_DRAWABLE_CARD_CELL_HPP
#define _GAME_DRAWABLE_CARD_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "../../../Player.hpp"
#include "../Cards/CardDeck.hpp"


class DrawableCardCell: public Cell {

	CardDeck* deck;
    
	void drawACard();

public:

	DrawableCardCell(int pos, CardDeck* one_deck): Cell{pos}, deck{one_deck} {};
    
	void action(Player* player);

};

#endif

#ifndef _GAME_DRAWABLE_CARD_CELL_HPP
#define _GAME_DRAWABLE_CARD_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "../Cards/CardDeck.hpp"


class Player;

class DrawableCardCell: public Cell {

	//CardDeck* deck;
    std::shared_ptr<CardDeck> deck;
    
	void drawACard();

public:

	//DrawableCardCell(int pos, CardDeck* one_deck): Cell{pos}, deck{one_deck} {};
	DrawableCardCell(int pos, std::shared_ptr<CardDeck> one_deck): Cell{pos}, deck{one_deck} {};

	void action(Player* player); 
	
	
									//card = deck.drawCard() prendre une random dans cet array
                                    // card.action(player)
};

#endif

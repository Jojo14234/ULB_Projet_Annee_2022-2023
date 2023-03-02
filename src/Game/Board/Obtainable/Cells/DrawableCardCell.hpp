#ifndef _GAME_DRAWABLE_CARD_CELL_HPP
#define _GAME_DRAWABLE_CARD_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "../Cards/CardDeck.hpp"


class Player;

class DrawableCardCell: public Cell {

	CardDeck* deck;
    
	void drawACard();

public:

	DrawableCardCell(int pos, CardDeck* one_deck): Cell{pos}, deck{one_deck} {};
    
	void action(Player* player) {
		Card* drawed_card = deck->drawACard();
		player->getClient()->send("Vous avez piocher cette carte: ");
		player->getClient()->send(drawed_card->getDesciption());
		drawed_card->action(player);
	}    
	
	
									//card = deck.drawCard() prendre une random dans cet array
                                    // card.action(player)
};

#endif

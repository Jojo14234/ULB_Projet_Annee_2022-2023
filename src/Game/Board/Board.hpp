#ifndef _GAME_BOARD_HPP
#define _GAME_BOARD_HPP

#include "Obtainable/Cards/CardDeck.hpp"
#include "Obtainable/Cells/Cell.hpp"

#include <array>
#include <memory>


class Board {

	// community card deck
	CardDeck community_deck;
	
	// lucky card deck
	CardDeck lucky_deck;
	
	// cells
	std::array<std::shared_ptr<Cell>, 40> cells;

	// init all cells
	void initAllCells();
	
	// init all decks
	void initAllDecks();

public:

	Board() { this->initAllCells(); this->initAllDecks(); }

};

#endif 

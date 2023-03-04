#ifndef _GAME_BOARD_HPP
#define _GAME_BOARD_HPP

#include "Obtainable/Cards/CardDeck.hpp"
#include "Obtainable/Cells/Cell.hpp"
#include "../../utils/Configs.hpp"
#include "Obtainable/Cells/LandCell.hpp"


#include <array>
#include <memory>
#include <string>


class Board {

	// community card deck
	CardDeck community_deck;
	
	// lucky card deck
	CardDeck lucky_deck;
	
	// cells
	std::array<std::shared_ptr<Cell>, BOARD_SIZE> cells;

	// init all decks
	void initAllDecks();

	// init all cells
	void initAllCells();
	void initAllLand();
	void initOtherCells();
	
	
public:

	Board() { this->initAllDecks(); this->initAllCells(); }

    Cell* getCellByIndex();

    LandCell* getCellByName(std::string &name);



};

#endif 

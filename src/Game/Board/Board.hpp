#ifndef _GAME_BOARD_HPP
#define _GAME_BOARD_HPP

//#include "Obtainable/Cells/Cell.hpp"
#include "../../utils/Configs.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cards/CardDeck.hpp"

#include "json/json.h"

#include <array>
#include <memory>
#include <string>

class Cell;

class Board {

	// community card deck
	CardDeck* community_deck;
	
	// lucky card deck
	CardDeck* lucky_deck;
	
	// cells
	std::array<std::shared_ptr<Cell>, BOARD_SIZE> cells;

	// init all decks
	void initAllDecks();

	// init all cells
	void initAllCells();
	void initAllLand();
	void initOtherCells();

	
public:

	Board() { std::cout<<"in board constructor"<<std::endl; initAllDecks(); initAllCells(); std::cout<<"finish board constructor"<<std::endl;}

    Cell* getCellByIndex(int index);

    LandCell* getCellByName(std::string &name);

    std::array<std::shared_ptr<Cell>, BOARD_SIZE> getAllCells() {return cells;}

};

#endif 

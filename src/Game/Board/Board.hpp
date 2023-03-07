#ifndef _GAME_BOARD_HPP
#define _GAME_BOARD_HPP

//#include "Obtainable/Cells/Cell.hpp"
#include "../../utils/Configs.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cards/CardDeck.hpp"

#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

#include <array>
#include <memory>
#include <string>

class Cell;

class Board {

    //TODO test (rémy)
    std::shared_ptr<CardDeck> community_deck;
    std::shared_ptr<CardDeck> lucky_deck;

	// community card deck
	//CardDeck* community_deck;
	// lucky card deck
	//CardDeck* lucky_deck;
	
	// cells
	std::array<std::shared_ptr<Cell>, BOARD_SIZE> cells;

	// init all decks
	void initAllDecks();

	// init all cells
	void initAllCells();
	void initAllLand();

    void extractProperty(Json::Value &list);
	void initOtherCells();

	
public:

	Board();

    //TODO change into smartPointer
	//~Board() { delete community_deck; delete lucky_deck; }


    Cell* getCellByIndex(int index);

    LandCell* getCellByName(std::string &name);

    //TODO ici on renvoie une copie, on pourrait renvoyer un pointeur vers le vecteur ?
    std::array<std::shared_ptr<Cell>, BOARD_SIZE> getAllCells() { return cells; }

};

#endif 

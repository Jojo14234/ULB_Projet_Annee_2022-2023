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

    std::shared_ptr<CardDeck> community_deck;
    std::shared_ptr<CardDeck> lucky_deck;

	// cells
	std::array<std::shared_ptr<Cell>, BOARD_SIZE> cells;

	// init decks cells
	void initDecksCardLand();

	// init property cells
	void initPropertyLand();
    void initNonPropertyLand();

    template<typename T>
    void extractProperty(Json::Value &list);
    void extractDeckCard(Json::Value &list, std::shared_ptr<CardDeck> deck);
	
public:

	Board();
    ~Board()=default;

    Cell* getCellByIndex(int index);

    LandCell* getCellByName(const std::string &name);

    //TODO ici on renvoie une copie, on pourrait renvoyer un pointeur vers le vecteur ?
    std::array<std::shared_ptr<Cell>, BOARD_SIZE> getAllCells() { return cells; }

};

#endif 

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
#include <vector>

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
    void extractDeckCard(Json::Value &list, std::shared_ptr<CardDeck> deck, std::string name);
	
public:

	Board();
    ~Board()=default;

    Cell* operator[](int index);

    LandCell* getCellByName(const std::string &name);

    std::shared_ptr<CardDeck> getLuckyDeck();
    std::shared_ptr<CardDeck> getCommuDeck();




};

#endif 

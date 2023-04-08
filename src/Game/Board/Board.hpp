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
#include "Obtainable/Cells/Land/Land.hpp"

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

    CardDeck* getDeckByName(std::string name) {
        if (name == "LUCKY DECK") { return this->lucky_deck.get(); }
        else {return this->community_deck.get(); }
    }

    std::vector<Land*> getAllAvailableLand() {
        std::vector<Land*> available_land;
        for (auto cell : cells){
            if (cell.get()->isLandCell()){
                LandCell* l = dynamic_cast<LandCell*>(cell.get());
                if (l->getLand()->getStatus() == LAND_STATUS::FREE){
                    available_land.push_back(l->getLand());
                }
            }
        }
        return available_land;
    }

    int getBoardSize(){
        return cells.size();
    }

};

#endif 

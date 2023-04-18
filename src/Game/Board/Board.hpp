#ifndef _GAME_BOARD_HPP
#define _GAME_BOARD_HPP

//jsoncpp
#include "../../jsoncpp/include/json/allocator.h"
#include "../../jsoncpp/include/json/assertions.h"
#include "../../jsoncpp/include/json/config.h"
#include "../../jsoncpp/include/json/forwards.h"
#include "../../jsoncpp/include/json/json_features.h"
#include "../../jsoncpp/include/json/json.h"
#include "../../jsoncpp/include/json/reader.h"
#include "../../jsoncpp/include/json/value.h"
#include "../../jsoncpp/include/json/version.h"
#include "../../jsoncpp/include/json/writer.h"

#include <array>
#include <memory>
#include <string>
#include <vector>
#include "Obtainable/Cells/Land/Land.hpp"

#include "../../Utils/Config/Configs.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cards/CardDeck.hpp"
#include "Obtainable/Cells/Land/Property.hpp"

class Cell;

class Board {

    std::shared_ptr<CardDeck> community_deck = std::make_shared<CardDeck>("COMMUNITY DECK");
    std::shared_ptr<CardDeck> lucky_deck = std::make_shared<CardDeck>("LUCKY DECK");

    // Constructeur
    int hotel_remaining;
    int home_remaining;

	// cells
	std::array<std::shared_ptr<Cell>, BOARD_SIZE> cells;

    // INIT
    void initPropertyLand();
    void initNonPropertyLand();
	void initDecksCardLand();

    // EXTRACT from Json::Value
    template<typename T>
    void extractLands(Json::Value &lands);
    template<typename T>
    std::shared_ptr<T> extractLand(Json::Value &land);
    void extractProperties(Json::Value &properties);
    std::shared_ptr<Property> extractProperty(Json::Value &prop);
    void extractDeckCard(Json::Value &list, std::string name);

public:

	Board(int max_home = MAX_HOME , int max_hotel = MAX_HOTEL);
    ~Board()=default;



    // GETTER
    LandCell* getLandCell(const std::string &name) const;
    std::shared_ptr<CardDeck> getDeck(std::string name) const;
    std::shared_ptr<CardDeck> getLuckyDeck() const;
    std::shared_ptr<CardDeck> getCommunityDeck() const;

    // SETTER
    int& getRemainingHome();
    int& getRemainingHotel();

    // OPERATION
    Cell* operator[](int index);

    LandCell* getCellByName(const std::string &name);

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

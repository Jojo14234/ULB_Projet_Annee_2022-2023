#ifndef _GAME_BOARD_HPP
#define _GAME_BOARD_HPP

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

#include "../../utils/Configs.hpp"
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


};

#endif 

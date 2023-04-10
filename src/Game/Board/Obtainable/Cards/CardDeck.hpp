#ifndef _GAME_CARD_DECK_HPP
#define _GAME_CARD_DECK_HPP


#include <string>
#include <array>
#include <memory>
#include <fstream>

#include "Card.hpp"


// Jsonlib
#include "../../../../jsoncpp/include/json/allocator.h"
#include "../../../../jsoncpp/include/json/assertions.h"
#include "../../../../jsoncpp/include/json/config.h"
#include "../../../../jsoncpp/include/json/forwards.h"
#include "../../../../jsoncpp/include/json/json_features.h"
#include "../../../../jsoncpp/include/json/json.h"
#include "../../../../jsoncpp/include/json/reader.h"
#include "../../../../jsoncpp/include/json/value.h"
#include "../../../../jsoncpp/include/json/version.h"
#include "../../../../jsoncpp/include/json/writer.h"



class CardDeck {
	
	std::array<std::shared_ptr<Card>, 16> card_list; // + ajouter carte prison
    std::string name;

    void extractMoneyCard(Json::Value &cards, int &idx);
    void extractCellCard(Json::Value &cards, int &idx);
    void extractJailCard(Json::Value &cards, int &idx);
    std::array<int, 4> extractStationsArray(Json::Value &cards);

public:

	CardDeck()=default;

	CardDeck(std::string name);

	Card* drawACard();

    bool isJailCardInside();

    void replaceJailCard();

    void debugInfoDescription();

};

#endif

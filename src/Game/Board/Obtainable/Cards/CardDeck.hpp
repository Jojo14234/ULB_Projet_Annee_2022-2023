#ifndef _GAME_CARD_DECK_HPP
#define _GAME_CARD_DECK_HPP

#include <string>
#include <json/json.h>
#include <array>
#include <memory>

#include "Card.hpp"
#include "MoneyCard.hpp"
#include "CellCard.hpp"


class CardDeck {
	
	std::array<std::shared_ptr<Card>, 16> card_list; // + ajouter carte prison

public:

	CardDeck()=default;

	CardDeck(std::string name) {
		Json::Value root;
		Json::Reader reader;
		std::ifstream file("data/card_data.json");
		if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

		Json::Value deck = root[name];
		//iterer dans money puis cell rajouter shr ptr dans liste
		Json::Value money_card_set = root[name]["MoneyCard"];
		Json::Value cell_card_set = root[name]["CellCard"];

		int idx=0;  //de la liste de carte
		for (unsigned int i=0; i<money_card_set.size(); i++){
			this->card_list[idx] = std::make_shared<MoneyCard>(money_card_set[i]);
			idx++;
		}
		for (unsigned int i=0; i<cell_card_set.size(); i++){
			this->card_list[idx] = std::make_shared<CellCard>(cell_card_set[i]);
			idx++;
		}
		//ajout 2 cartes prison !!!
	}

};

#endif

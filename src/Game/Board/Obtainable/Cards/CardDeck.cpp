#include <random>
#include <iostream>
#include "CardDeck.hpp"

#include "Card.hpp"
#include "MoneyCard.hpp"
#include "CellCard.hpp"
#include "../../../../utils/Configs.hpp"


CardDeck::CardDeck(std::string name): name{name} {
	Json::Value root;
	std::ifstream file(CARD_DATA, std::ifstream::binary);
    file >> root;

	int idx=0;  //indexe de la liste de carte
    // Add all the card that leads to pay money
    //Json::Value money_card = root[name]["MoneyCard"];		//for refactor construct parameter !!
	for (unsigned int i=0; i < root[name]["MoneyCard"].size(); i++) {
		this->card_list[idx] = std::make_shared<MoneyCard>(root[name]["MoneyCard"][i]);
		idx++;
	}
    // Add all the card that lead to a cells
    for (unsigned int i=0; i < root[name]["CellCard"].size(); i++) {
		this->card_list[idx] = std::make_shared<CellCard>(root[name]["CellCard"][i]);
		idx++;
	}
    // Add Jail card to the deck
    this->card_list[idx] = std::make_shared<JailCard>(root[name]["JailCard"]);

    std::cout << "[init all     " << name << " : 100%]" << std::endl;
}

Card* CardDeck::drawACard() {	//drawn !!!
	std::srand(time(0));
	while(true){
		int result = std::rand()% 16;
		Card* drawed_card = this->card_list.at(result).get();
		if (result!=15) {
			return drawed_card;
		}
		else {
			if (dynamic_cast<JailCard*>(drawed_card)->getOwner() == nullptr) {
                this->card_list.at(15) = nullptr;
				return drawed_card;
			}
		}
	}
}

bool CardDeck::isJailCardInside() {
    return this->card_list.at(15) != nullptr;
}

void CardDeck::replaceJailCard() {
    if (!isJailCardInside()) {
        Json::Value root;
        std::ifstream file(CARD_DATA, std::ifstream::binary);
        file >> root;
        this->card_list[15] = std::make_shared<JailCard>(root[this->name]["JailCard"]);
    }
}
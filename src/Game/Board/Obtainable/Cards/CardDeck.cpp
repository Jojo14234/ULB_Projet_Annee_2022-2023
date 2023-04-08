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
    Json::Value money_cards = root[name]["MoneyCard"];		//for refactor construct parameter !!


	for (unsigned int i=0; i < root[name]["MoneyCard"].size(); i++) {

        if (money_cards[i]["receive"] == -1){	//bday card
			Json::Value current = money_cards[i];
            std::string description = current["descript"].asString();
            int amount = current["amount"].asInt();
			this->card_list[idx] = std::make_shared<FromOtherMoneyCard>(description, amount, true);
		}
        else if (money_cards[i]["receive"] == -2) {	//choice card
			Json::Value current = money_cards[i];
            std::string description = current["descript"].asString();
            int amount = current["amount"].asInt();
			std::string deck_name = "LUCKY DECK";
			this->card_list[idx] = std::make_shared<ChoiceMoneyCard>(description, amount, false, deck_name);
		}
        this->card_list[idx] = std::make_shared<MoneyCard>(root[name]["MoneyCard"][i]);
		idx++;
	}

    // Add all the card that lead to a cells
    Json::Value cell_cards = root[name]["CellCard"];
    for (unsigned int i=0; i < cell_cards.size(); i++) {

    	if (cell_cards[i]["dest"].size() > 1) {	//tester si ça marche (size) !! et mettre tout ça dans dans une fonction ?

            Json::Value current = cell_cards[i];
    		std::array<int, 4> dest_list;
    		for (unsighed int i=0; i < current["dest"].size(); i++) {
                dest_list[i] = current["dest"][i].asInt();
            }

            std::string description = current["descript"].asString();
            bool money = current["money"].asBool();

    		this->card_list[idx] = std::make_shared<NearestCellCard>(description, money, dest_list);

        }
    	else if (cell_cards[i]["dest"].asInt() < 0) {
    		Json::Value current = cell_cards[i];
            std::string description = current["descript"].asString();
            bool money = current["money"].asBool();
            int destination = current["dest"].asInt();
            this->card_list[idx] = std::make_shared<MoveBackCellCard>(description, money, destination);
        }
    	else {
			this->card_list[idx] = std::make_shared<CellCard>(cell_cards[i]);

        }
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
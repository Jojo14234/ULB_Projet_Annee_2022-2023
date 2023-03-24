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


	for (unsigned int i=0; i < money_cards.size(); i++) {
        std::string description = money_cards[i]["descript"].asString();
        int amount = money_cards[i]["amount"].asInt();
        int receive = money_cards[i]["receive"].asInt();

        if (receive == -1) { // Birthday card
           this->card_list[idx] = std::make_shared<FromOtherMoneyCard>(description, amount, true);
        }
        else if (receive == -2) { // Choice card
            this->card_list[idx] = std::make_shared<ChoiceMoneyCard>(description, amount, false, "LUCKY_DECK");
        }
        else { // Other
            this->card_list[idx] = std::make_shared<MoneyCard>(description, amount, (bool)receive);
        }
        idx++;

        /*
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
         */
	}

    // Add all the card that lead to a cells
    Json::Value cell_cards = root[name]["CellCard"];

    for (unsigned int i=0; i < cell_cards.size(); i++) {

        std::string description = cell_cards[i]["descript"].asString();
        bool money = cell_cards[i]["money"].asBool();

        if (cell_cards[i]["dest"].size() == 1) {
            int destination = cell_cards[i]["dest"][0].asInt();
            // Cell card normal
            if (destination >= 0) { this->card_list[idx] = std::make_shared<CellCard>(description, money, destination); }
            // MoveBack card
            else { this->card_list[idx] = std::make_shared<MoveBackCellCard>(description, money, destination); }
        }
        else if (cell_cards[i]["dest"].size() > 1) {
            // Construction de l array des destination
            std::array<int, 4> dest_list;
            for (unsigned int i=0; i < cell_cards[i]["dest"].size(); i++) { dest_list[i] = cell_cards[i]["dest"][i].asInt(); }
            // Nearest Card
            this->card_list[idx] = std::make_shared<NearestCellCard>(description, money, dest_list);
        }
        idx++;

        /*
    	if (cell_cards[i]["dest"].size() > 1) {	//tester si ça marche (size) !! et mettre tout ça dans dans une fonction ?
    		std::array<int, 4> dest_list;
    		for (int i=0; i < cell_cards[i]["dest"].size(); i++) {
                dest_list[i] = cell_cards[i]["dest"][i].asInt();
            }

    		this->card_list[idx] = std::make_shared<NearestCellCard>(description, money, dest_list);

        }
    	else if (cell_cards[i]["dest"].asInt() < 0) {
            int destination = cell_cards[i]["dest"].asInt();
            this->card_list[idx] = std::make_shared<MoveBackCellCard>(description, money, destination);
        }
    	else {
			this->card_list[idx] = std::make_shared<CellCard>(cell_cards[i]);

        }
        */

    }

    // Add Jail card to the deck
    std::string description = root[name]["JailCard"]["descript"].asString();
    this->card_list[idx] = std::make_shared<JailCard>(description);

    std::cout << "[init all     " << name << " : 100%]" << std::endl;
}

Card* CardDeck::drawACard() {	//drawn !!!
	std::srand(time(0));
    Card* drawn_card;
	while(true) {
		int result = std::rand()% 16;
		drawn_card = this->card_list.at(result).get();
		if (result != 15) { break; }
        if (isJailCardInside()) { break; }
	}
    return drawn_card;
}

bool CardDeck::isJailCardInside() {
    return dynamic_cast<JailCard*>(this->card_list.at(15).get())->getOwner() == nullptr;
}

void CardDeck::replaceJailCard() {
    dynamic_cast<JailCard*>(this->card_list.at(15).get())->setOwner(nullptr);
}
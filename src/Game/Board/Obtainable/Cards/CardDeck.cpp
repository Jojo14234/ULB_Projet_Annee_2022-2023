#include <random>
#include "CardDeck.hpp"

#include "Card.hpp"
#include "MoneyCard.hpp"
#include "CellCard.hpp"



virtual void CellCard::action(Player* player) {
    player->getClient()->send("Vous vous déplacez à la case "+ std::to_string(dest));
    player->move(player->getClient()->getGameServer()->getGame()->getBoard()->getCellByIndex(dest), gain_money);	//get cell by index
};

/*void MoneyCard::action(Player* player) {
		if (receive) {
			player->receive(amount, "Bank");
			player->getClient()->send("Vous recevez "+std::to_string(amount)+"$");
		}
		else {
			if (amount != 0) { player->pay(amount, true); player->getClient()->send("Vous payez "+std::to_string(amount));}
			else {
				std::vector<Property*> properties = player->getAllProperties();
				for ( auto &elem : properties ){
					if (elem->getLevel() <= 4) { player->pay(amount_house, true); }
					else if (elem->getLevel() == 5) { player->pay(amount_hotel, true); }
				}
			}
		}
	};*/	

CardDeck::CardDeck(std::string name) {
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
		this->card_list[idx] = std::make_shared<JailCard>(root[name]["JailCard"]);
	}

CardDeck::Card* drawACard() {
		std::srand(time(0));
		while(true){
			int result = std::rand()% 16;
			Card* drawed_card = card_list.at(result);
			if (result!=15) {
				return drawed_card;
			}
			else {
				if (dynamic_cast<JailCard*>(drawed_card)->getOwner() == nullptr) {return drawed_card;}
			}
		}
		
	 }
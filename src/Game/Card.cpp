#include "Card.hpp"

CardDeck::CardDeck(std::string deck_name){
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/card_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

    Json::Value deck = root[deck_name];
    //iterer dans money puis cell rajouter shr ptr dans liste
    Json::Value money_card_set = root[deck_name]["MoneyCard"]
    Json::Value cell_card_set = root[deck_name]["CellCard"]

    int idx=0;
    for (unsigned int i=0; i<money_card_set.size(); i++){
        this->card_list[idx] = std::make_shared<CardMoney>(money_card_set[i]);
        idx++;
    }
    for (unsigned int i=0; i<cell_card_set.size(); i++){
        this->card_list[idx] = std::make_shared<CellMoney>(cell_card_set[i]);
        idx++;
    }
    //ajout 2 cartes prison
}


//###################################################
Card::Card(Json::Value &info){
    //this->description = (card_nO <= 20) ? root["MoneyCard"][card_nO]["descript"] : root["CellCard"][card_nO]["descript"] ;
    this->description = info["descript"];
}

//-------------------------------
CardCell::CardCell(Json::Value &info_cell_card){
    this->dest = info_cell_card["dest"];
    this->gain_money = info_cell_card["dest"];
}

//-------------------------------
Cardmoney::CardMoney(Json::Value &info_money_card){
    this->amount = info_money_card["amount"];
    this->amount_house = info_money_card["amount_house"];
    this->amount_hotel = info_money_card["amount_hotel"]
}

//-------------------------------
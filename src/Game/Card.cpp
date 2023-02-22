#include "Card.hpp"

LuckyCardDeck::LuckyCardDeck(){
    for (size_t i = 0; i < money_card_n0.size(); ++i){
        this->card_list[i] = CardMoney(money_card_nO[i]);
    }
    for (size_t i = 0; i < cell_card_n0.size(); ++i){
        this->card_list[i] = CardCell(money_card_nO[i]);
    }
}

//-------------------------------
CommunityCardDeck::CommunityCardDeck(){
    
}

//###################################################
Card::Card(int card_nO){
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/card_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

    this->description = (card_nO <= 20) ? root["MoneyCard"][card_nO]["descript"] : root["CellCard"][card_nO]["descript"] ;
}

//-------------------------------
CardCell::CardCell(int card_nO){
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/card_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

    this->dest = root[CellCard][card_nO]["dest"] ;
    this->gain_money = root[CellCard][card_nO]["money"] ;
}

//-------------------------------

//-------------------------------
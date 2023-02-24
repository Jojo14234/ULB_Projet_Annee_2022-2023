//
// Created by Joachim on 14/02/2023.
//

#include "Board.hpp"

Board::initAllDecks(){
	this->community_deck = CardDeck("COMMUNITY DECK")
	this->lucky_deck = CardDeck("LUCKY DECK");
}



Board::initAllCells(){
	//init property
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/property_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

	int nbr_property = root["No property"]; //.asInt() ?
	for (int i=0; i<nbr_property; i++){
		int pos = root["PROPERTY"][i]["pos"]
		Property prop = Property(root["PROPERTY"][i])	//ieme propriété dans json
		this->cells[pos] = std::make_shared<PropertyCell>(pos, prop);
	}
}


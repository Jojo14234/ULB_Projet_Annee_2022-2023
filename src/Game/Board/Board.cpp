#include "Board.hpp"
#include "Obtainable/Cells/PropertyCell.hpp"


void Board::initAllDecks(){
	this->community_deck = CardDeck("COMMUNITY DECK");
	this->lucky_deck = CardDeck("LUCKY DECK");
}


void Board::initAllCells(){
	//init property
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/property_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

	int nbr_property = root["No property"].asInt();
	for (int i=0; i<nbr_property; i++){
		int pos = root["PROPERTY"][i]["pos"].asInt();
		Property prop = Property(root["PROPERTY"][i]);	//ieme propriété dans json
		this->cells[pos] = std::make_shared<PropertyCell>(pos, prop);
	}
}


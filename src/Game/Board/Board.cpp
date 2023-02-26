#include "Board.hpp"
#include "Obtainable/Cells/PropertyCell.hpp"


void Board::initAllDecks(){
	this->community_deck = CardDeck("COMMUNITY DECK");
	this->lucky_deck = CardDeck("LUCKY DECK");
}

void Board::initAllLand(){
	//init property
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/property_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

	Json::Value prop_list = root["PROPERTY"];

	for (unsigned int i=0; i<property_list.size(); i++){
		int pos = prop_list[i]["pos"].asInt();
		Property prop = Property(prop_list[i]);	//ieme propriété dans json
		this->cells[pos] = std::make_shared<PropertyCell>(pos, prop); 	//alt pour pos, Property.getPos() ?
	}
}

void Board::initOtherCells(){
	Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/cell_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

	//go to jail
	int pos = root["Go to jail"]["pos"].asInt();
	this->cells[pos] = make_shared<GoJailCell>(pos);

	//jail
	int pos = root["Jail"]["pos"].asInt();
	this->cells[pos] = make_shared<JailCell>(pos);

	//parking
	Json::Value parking = root["Parking"];
	int pos = parking["pos"].asInt();
	this->cells[pos] = make_shared<ParkingCell>(pos);

	//draw card
	Json::Value draw_list = root["DRAW CARD"];
	for (unsigned int i=0; draw_list.size(); i++){
		int pos = draw_list[i]["pos"].asInt();
		CardDeck* deck = (draw_list[i]["type"].asString()=="LUCKY DECK") ? this->lucky_deck : this->community_deck;
		this->cells[pos] = std::make_shared<DrawableCardCell>(pos, deck);
	}

	//tax
	Json::Value tax_list = root["TAX"];
	for (unsigned i=0; i<tax_list.size(); i++){
		int pos tax_list[i]["pos"].asInt();
		this->cells[pos] = std::make_shared<TaxCell>(tax_list)
	}


}

void Board::initAllCells(){
	this->initAllLand();
	this->initOtherCells()

}


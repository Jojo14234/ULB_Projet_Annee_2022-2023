#include "Board.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cells/JailCell.hpp"
#include "Obtainable/Cells/ParkingCell.hpp"
#include "Obtainable/Cells/GoJailCell.hpp"
#include "Obtainable/Cells/DrawableCardCell.hpp"
#include "Obtainable/Cells/TaxCell.hpp"


void Board::initAllDecks(){
    CardDeck deck = CardDeck("COMMUNITY DECK");
	this->community_deck = &deck;
    deck = CardDeck("LUCKY DECK");
	this->lucky_deck = &deck;
}

void Board::initAllLand(){
	//init property
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/property_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

	Json::Value prop_list = root["PROPERTY"];

	for (unsigned int i=0; i<prop_list.size(); i++){
		int pos = prop_list[i]["pos"].asInt();
		Property prop = Property(prop_list[i]);	//ieme propriété dans json
		this->cells[pos] = std::make_shared<LandCell>(pos, &prop); 	//alt pour pos, Property.getPos() ?
	}

	Json::Value station_list = root["STATION"];
	for (unsigned int i=0; i<station_list.size(); i++) {
		int pos = station_list[i]["pos"].asInt();
		Station stat = Station(station_list[i]);
		this->cells[pos] = std::make_shared<LandCell>(pos, &stat);
	}

	Json::Value company_list = root["COMPANY"];
	for (unsigned int i=0; i<company_list.size(); i++) {
		int pos = station_list[i]["pos"].asInt();
		Company comp = Company{company_list[i]};
		this->cells[pos] = std::make_shared<LandCell>(pos, &comp);
	}
}

void Board::initOtherCells(){
	Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/cell_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }

	//go to jail
	int pos = root["Go to jail"]["pos"].asInt();
	this->cells[pos] = std::make_shared<GoJailCell>(pos);

	//jail
	pos = root["Jail"]["pos"].asInt();
	this->cells[pos] = std::make_shared<JailCell>(pos);

	//parking
	Json::Value parking = root["Parking"];
	pos = parking["pos"].asInt();
	this->cells[pos] = std::make_shared<ParkingCell>(pos);

	//draw card
	Json::Value draw_list = root["DRAW CARD"];
	for (unsigned int i=0; draw_list.size(); i++){
		pos = draw_list[i]["pos"].asInt();
		CardDeck* deck = (draw_list[i]["type"].asString()=="LUCKY DECK") ? this->lucky_deck : this->community_deck;
		this->cells[pos] = std::make_shared<DrawableCardCell>(pos, deck);
	}

	//tax
	Json::Value tax_list = root["TAX"];
	for (unsigned i=0; i<tax_list.size(); i++){
		pos = tax_list[i]["pos"].asInt();
		this->cells[pos] = std::make_shared<TaxCell>(tax_list);
	}
}

void Board::initAllCells(){
	this->initAllLand();
	this->initOtherCells();

}

Cell* Board::getCellByIndex(int index){
    return cells.at(index).get();
}

LandCell* Board::getCellByName(std::string &name){
    LandCell* land_cell = nullptr; //TODO temp soltion, ask Hugo si ça lui semble logique
    for (auto cell : cells){
        land_cell = dynamic_cast<LandCell*>(cell.get());
        if (land_cell != nullptr){
            if (land_cell->getLand()->getName() == name){
                return land_cell;
            }
        }
    }
    return nullptr;
}


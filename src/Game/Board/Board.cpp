#include "Board.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cells/JailCell.hpp"
#include "Obtainable/Cells/ParkingCell.hpp"
#include "Obtainable/Cells/GoJailCell.hpp"
#include "Obtainable/Cells/DrawableCardCell.hpp"
#include "Obtainable/Cells/TaxCell.hpp"


void Board::initAllDecks(){
    //TODO : ca c'est pas vrai, à changer (rémy)
    CardDeck deck = CardDeck("COMMUNITY DECK");
	this->community_deck = &deck;
    deck = CardDeck("LUCKY DECK");
	this->lucky_deck = &deck;
}

void Board::initAllLand(){
	//init property
    Json::Value root;
	std::ifstream file("Game/Board/Obtainable/data/property_data.json");
    file >> root;

	Json::Value prop_list;
    prop_list = root["PROPERTY"];

	for (unsigned int i=0; i < prop_list.size(); i++) {
		int pos = prop_list[i]["pos"].asInt();	//ieme propriété dans json
		this->cells.at(pos) = std::make_shared<LandCell>(pos, std::make_shared<Property>(prop_list[i])); 	//alt pour pos, Property.getPos() ?
	}

	Json::Value station_list;
    station_list = root["STATION"];

	for (unsigned int i=0; i<station_list.size(); i++) {
        int pos = station_list[i]["pos"].asInt();
		this->cells.at(pos) = std::make_shared<LandCell>(pos, std::make_shared<Station>(station_list[i]));
	}

	Json::Value company_list;
    company_list = root["COMPANY"];

	for (unsigned int i=0; i<company_list.size(); i++) {
		int pos = station_list[i]["pos"].asInt();
		this->cells.at(pos) = std::make_shared<LandCell>(pos, std::make_shared<Company>(company_list[i]));
	}
    std::cout << "InitAllLand done" << std::endl;
}

void Board::initOtherCells(){
	Json::Value root;
	std::ifstream file("Game/Board/Obtainable/data/cell_data.json");
    file >> root;

	//go to jail
	int pos = root["Go to jail"]["pos"].asInt();
	this->cells.at(pos) = std::make_shared<GoJailCell>(pos);
    //pos = 30

	//jail
	pos = root["Jail"]["pos"].asInt();
	this->cells.at(pos) = std::make_shared<JailCell>(pos);
    //pos = 10

	//parking
	Json::Value parking;
    parking = root["Parking"];
	pos = parking["pos"].asInt();
	this->cells.at(pos) = std::make_shared<ParkingCell>(pos);
    //pos = 20

	//case départ
	pos = 0;
	this->cells.at(pos) = std::make_shared<ParkingCell>(pos);
    //pos = 0

	//draw card
	Json::Value draw_list;
    draw_list = root["DRAW CARD"];

    std::cout << "Draw list size : " << draw_list.size() << std::endl;

	for (unsigned int i = 0; i < draw_list.size(); i++) {
		pos = draw_list[i]["pos"].asInt();
		CardDeck* deck = (draw_list[i]["type"].asString() == "LUCKY DECK") ? this->lucky_deck : this->community_deck;
		this->cells.at(pos) = std::make_shared<DrawableCardCell>(pos, deck);
	}

	//tax
	Json::Value tax_list;
    tax_list = root["TAX"];

    std::cout << "Tax list size : " << tax_list.size() << std::endl;
    std::cout << tax_list << std::endl;

	for (unsigned i = 0; i < tax_list.size(); i++){
		int pos = tax_list[i]["pos"].asInt();
        int amount = tax_list[i]["amount"].asInt();
        std::string type = tax_list[i]["type"].asString();

		this->cells.at(pos) = std::make_shared<TaxCell>(pos, amount, type);
	}

    std::cout << "InitOtherCells done" << std::endl;
}

void Board::initAllCells(){
	this->initAllLand();
	this->initOtherCells();
    std::cout << "Done" << std::endl;

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


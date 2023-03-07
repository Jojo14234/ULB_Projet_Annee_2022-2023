#include <iostream>
#include "Board.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cells/JailCell.hpp"
#include "Obtainable/Cells/ParkingCell.hpp"
#include "Obtainable/Cells/GoJailCell.hpp"
#include "Obtainable/Cells/DrawableCardCell.hpp"
#include "Obtainable/Cells/TaxCell.hpp"
#include "../../utils/Configs.hpp"


Board::Board() {
    std::cout << "-----Start Board constructor-----" << std::endl;
    initAllDecks();
    initAllCells();
    std::cout<<"-----Finish board constructor-----"<<std::endl;
}

void Board::initAllDecks(){
    this->community_deck = std::make_shared<CardDeck>("COMMUNITY DECK");
    this->lucky_deck = std::make_shared<CardDeck>("LUCKY DECK");
}

void Board::initAllLand(){
	//init property
    Json::Value root;
	std::ifstream file(PROPERTY_DATA);
    file >> root;

	Json::Value property_list = root["PROPERTY"];
    this->extractProperty(property_list);
    Json::Value station_list = root["STATION"];
    this->extractProperty(station_list);
    Json::Value company_list = root["COMPANY"];
    this->extractProperty(company_list);

    std::cout << "InitAllLand done" << std::endl;
}

void Board::extractProperty(Json::Value &list) {
    // Pas de couleur, mais pas de panic ça fonctionne
    for (auto property : list) {
        int position = property["pos"].asInt();
        this->cells.at(position) = std::make_shared<LandCell>(position, std::make_shared<Property>(property));
    }
}


void Board::initOtherCells(){
	Json::Value root;
	std::ifstream file(CELL_DATA);
    file >> root;

    int start_position = root["Start"]["pos"].asInt();
	int position_go_jail = root["Go to jail"]["pos"].asInt();
    int position_jail = root["Jail"]["pos"].asInt();
    int position_parking = root["Parking"]["pos"].asInt();
    this->cells.at(start_position) = std::make_shared<ParkingCell>(start_position);
	this->cells.at(position_go_jail) = std::make_shared<GoJailCell>(position_go_jail);
	this->cells.at(position_jail) = std::make_shared<JailCell>(position_jail);
    this->cells.at(position_parking) = std::make_shared<ParkingCell>(position_parking);
    std::cout << "All special cells done" << std::endl;

	//draw card & tax
	Json::Value community_card_list = root["DRAW CARD"]["COMMUNITY"];
	Json::Value lucky_card_list = root["DRAW CARD"]["LUCKY"];
    Json::Value tax_list = root["TAX"];

    for (auto card : community_card_list) {
        int position = card["pos"].asInt();
        this->cells.at(position) = std::make_shared<DrawableCardCell>(position, this->community_deck);
    }

    for (auto card : lucky_card_list) {
        int position = card["pos"].asInt();
        this->cells.at(position) = std::make_shared<DrawableCardCell>(position, this->lucky_deck);
    }

    for (auto tax : tax_list) {
        int position = tax["pos"].asInt();
        int amount = tax["amount"].asInt();
        std::string type = tax["type"].asString();
        this->cells.at(position) = std::make_shared<TaxCell>(position, amount, type);
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


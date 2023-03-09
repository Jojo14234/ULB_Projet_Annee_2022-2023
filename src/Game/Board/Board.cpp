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
    /*
     * 1. init board cells
     * 1.a Case achetable
     * 1.b Case non-achetable
     * 1.c Case community/Case chance
     */
    this->initPropertyLand();
    this->initNonPropertyLand();
    this->initDecksCardLand();
    std::cout<<"-----Finish board constructor-----"<<std::endl;
}

void Board::initDecksCardLand(){
    this->community_deck = std::make_shared<CardDeck>("COMMUNITY DECK");
    this->lucky_deck = std::make_shared<CardDeck>("LUCKY DECK");

    Json::Value root;
    std::ifstream file(CELL_DATA);
    file >> root;

    //draw card land
    Json::Value community_card_list = root["DRAW CARD"]["COMMUNITY"];
    this->extractDeckCard(community_card_list, this->community_deck);
    Json::Value lucky_card_list = root["DRAW CARD"]["LUCKY"];
    this->extractDeckCard(lucky_card_list, this->lucky_deck);
    std::cout << "[Init all    deck card lands : 100%]" << std::endl;
}

void Board::initPropertyLand(){
    Json::Value root;
	std::ifstream file(PROPERTY_DATA);
    file >> root;

	Json::Value property_list = root["PROPERTY"];
    this->extractProperty<Property>(property_list);
    Json::Value station_list = root["STATION"];
    this->extractProperty<Station>(station_list);
    Json::Value company_list = root["COMPANY"];
    this->extractProperty<Company>(company_list);
    std::cout << "[Init all     property lands : 100%]" << std::endl;
}

void Board::initNonPropertyLand() {
    Json::Value root;
    std::ifstream file(CELL_DATA);
    file >> root;

    this->cells.at(root["Start"]["pos"].asInt())        = std::make_shared<ParkingCell>(root["Start"]["pos"].asInt());
    this->cells.at(root["Go to jail"]["pos"].asInt())   = std::make_shared<GoJailCell>(root["Go to jail"]["pos"].asInt());
    this->cells.at(root["Jail"]["pos"].asInt())         = std::make_shared<JailCell>(root["Jail"]["pos"].asInt());
    this->cells.at(root["Parking"]["pos"].asInt())      = std::make_shared<ParkingCell>(root["Parking"]["pos"].asInt());

    for (auto tax : root["TAX"]) {
        int position = tax["pos"].asInt();
        int amount = tax["amount"].asInt();
        std::string type = tax["type"].asString();
        this->cells.at(position) = std::make_shared<TaxCell>(position, amount, type);
    }
    std::cout << "[Init all non-property lands : 100%]" << std::endl;
}

template<typename T>
void Board::extractProperty(Json::Value &list) {
    // Pas de couleur, mais pas de panic ça fonctionne
    for (auto property : list) {
        int position = property["pos"].asInt();
        //std::string purchase_price = property["purchase_price"].asString();
        //std::string name = property["name"].asString();
        this->cells.at(position) = std::make_shared<LandCell>(position, std::make_shared<T>(property));
    }
}

void Board::extractDeckCard(Json::Value &list, std::shared_ptr<CardDeck> deck) {
    for (auto card : list) {
        int position = card["pos"].asInt();
        this->cells.at(position) = std::make_shared<DrawableCardCell>(position, deck);
    }
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
            else{
                land_cell = nullptr;
            }
        }
    }
    return land_cell;
}


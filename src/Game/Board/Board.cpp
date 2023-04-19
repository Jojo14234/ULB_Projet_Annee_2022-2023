#include <iostream>
#include <string>
#include "Board.hpp"
#include "Obtainable/Cells/LandCell.hpp"
#include "Obtainable/Cells/JailCell.hpp"
#include "Obtainable/Cells/ParkingCell.hpp"
#include "Obtainable/Cells/GoJailCell.hpp"
#include "Obtainable/Cells/DrawableCardCell.hpp"
#include "Obtainable/Cells/TaxCell.hpp"
#include "Obtainable/Cells/StartCell.hpp"
#include "../../Utils/Config/Configs.hpp"



Board::Board(int max_home, int max_hotel)
        : hotel_remaining{max_hotel}, home_remaining{max_home} {
    std::cout << "-----Start Board constructor-----" << std::endl;
    this->initPropertyLand();
    this->initNonPropertyLand();
    this->initDecksCardLand();
    std::cout<<"-----Finish board constructor-----"<<std::endl;
}

// PRIVATE
void Board::initPropertyLand(){
    Json::Value root;
	std::ifstream file(PROPERTY_DATA);
    file >> root;

	Json::Value property_list = root["PROPERTY"];
    Json::Value station_list = root["STATION"];
    Json::Value company_list = root["COMPANY"];

    this->extractProperties(property_list);
    this->extractLands<Station>(station_list);
    this->extractLands<Company>(company_list);
    std::cout << "[Init all     property lands : 100%]" << std::endl;
}

void Board::initNonPropertyLand() {
    Json::Value root;
    std::ifstream file(CELL_DATA);
    file >> root;

    this->cells.at(root["Start"]["pos"].asInt())        = std::make_shared<StartCell>(root["Start"]["pos"].asInt(), "Depart");
    this->cells.at(root["Jail"]["pos"].asInt())         = std::make_shared<JailCell>(root["Jail"]["pos"].asInt(), "Prison");
    this->cells.at(root["Parking"]["pos"].asInt())      = std::make_shared<ParkingCell>(root["Parking"]["pos"].asInt(), "Parc");
    JailCell* jail = dynamic_cast<JailCell*>(this->cells.at(root["Jail"]["pos"].asInt()).get());
    std::string name = "EnPrison";
    this->cells.at(root["Go to jail"]["pos"].asInt())   = std::make_shared<GoJailCell>(root["Go to jail"]["pos"].asInt(), jail, name);

    for (auto tax : root["TAX"]) {
        int position = tax["pos"].asInt();
        int amount = tax["amount"].asInt();
        std::string type = tax["type"].asString();
        this->cells.at(position) = std::make_shared<TaxCell>(position, amount, type);
    }
    std::cout << "[Init all non-property lands : 100%]" << std::endl;
}

void Board::initDecksCardLand() {

    Json::Value root;
    std::ifstream file(CELL_DATA);
    file >> root;

    //draw card land
    Json::Value community_card_list = root["DRAW CARD"]["COMMUNITY"];
    this->extractDeckCard(community_card_list, "COMMUNITY DECK");

    Json::Value lucky_card_list = root["DRAW CARD"]["LUCKY"];
    this->extractDeckCard(lucky_card_list, "LUCKY DECK");
    std::cout << "[Init all    deck card lands : 100%]" << std::endl;
}

template<typename T>
void Board::extractLands(Json::Value &lands) {
    for (auto land : lands) {
        std::shared_ptr<T> l = this->extractLand<T>(land);
        this->cells.at(l->getPosition()) = std::make_shared<LandCell>(l->getPosition(), l, l->getName());
    }
}

template<typename T>
std::shared_ptr<T> Board::extractLand(Json::Value &land) {
    std::string name = land["name"].asString();
    int position = land["pos"].asInt();
    int price = land["price"].asInt();
    return std::make_shared<T>(name, price, position);
}

void Board::extractProperties(Json::Value &properties) {
    for (auto prop : properties) {
        std::shared_ptr<Property> p = this->extractProperty(prop);
        this->cells.at(p->getPosition()) = std::make_shared<LandCell>(p->getPosition(), p, p->getName());
    }
}

std::shared_ptr<Property> Board::extractProperty(Json::Value &prop) {
    std::string name = prop["name"].asString();
    int price = prop["price"].asInt();
    int position = prop["pos"].asInt();
    int construct = prop["construct"].asInt();
    PROPERTY_COLOR color = static_cast<PROPERTY_COLOR>(prop["color"].asInt());
    std::array<int, 6> rents;
    for (unsigned int i = 0; i < prop["rent"].size(); i++) { rents[i] = prop["rent"][i].asInt(); }
    return std::make_shared<Property>(name, price, position, color, construct, rents);
}

void Board::extractDeckCard(Json::Value &list, std::string name) {
    for (auto card : list) {
        int position = card["pos"].asInt();
        this->cells.at(position) = std::make_shared<DrawableCardCell>(position, this->getDeck(name), name);
    }
}

// PUBLIC

// Getter
LandCell* Board::getLandCell(const std::string &name) const {
    for (auto cell : cells) {
        LandCell* land_cell = dynamic_cast<LandCell*>(cell.get());
        if ( !land_cell ) { continue; }
        if ( land_cell->getLand()->getName() == name ) { return land_cell; }
    }
    return nullptr;
}
std::shared_ptr <CardDeck> Board::getDeck(std::string name) const {
    if (name == "LUCKY DECK") { return this->lucky_deck; }
    else if ( name == "COMMUNITY DECK" ) { return this->community_deck; }
    else {return this->lucky_deck; }
}
std::shared_ptr <CardDeck> Board::getCommunityDeck() const {
    return this->community_deck;
}
std::shared_ptr <CardDeck> Board::getLuckyDeck() const {
    return this->lucky_deck;
}

// Setter
int& Board::getRemainingHome() { return this->home_remaining; }
int& Board::getRemainingHotel() { return this->hotel_remaining; }

// Opération
Cell* Board::operator[](int index) {
    return cells.at(index % BOARD_SIZE).get();
};











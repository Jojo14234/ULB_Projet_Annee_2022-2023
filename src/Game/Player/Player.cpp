//
// Created by Joachim on 14/02/2023.
//

#include "Player.hpp"
#include "BankAccount.hpp"
//#include "../../Server/ClientManager/ClientManager.hpp"


int Player::processRollDice(Dice &dice) {
    int result = this->roll(dice);
    // If no double then return
    if ( !dice.isDouble() ) { dice.resetDoubleCounter(); return result; }
    // if 3 double then go to jail
    if ( dice.getDoubleCounter() >= 3 ) { this->setStatus(JAILED); dice.resetDoubleCounter(); return 0; }
    // else just reset the setRolled because player will have to play again
    this->setRolled(false);
    return result;
}

/*
 * Return a string formatted with all the infos about the roll dice
 * r1 = result of the first die
 * r2 = result of the second die
 * r = Result of both die (r1 + r2)
 * d = is double ? (0 false, true 1)
 * dc = double counter;
 */
std::string Player::rollInfos(Dice &dice) {
    std::string r1 = std::to_string(dice.getDice1());
    std::string r2 = std::to_string(dice.getDice2());
    std::string r = std::to_string(dice.getResults());
    std::string d = std::to_string(dice.isDouble());
    std::string dc = std::to_string(dice.getDoubleCounter());
    return r1 + ":" + r2 + ":" + r + ":" + d + ":" + dc;
}

// BOTH processMove are Use
void Player::processMove(Cell* new_cell, bool gainMoneyIfPassByStart) {
    if ( gainMoneyIfPassByStart && this->current_cell->getPosition() > new_cell->getPosition() ) {
        this->receive(STARTING_MONEY, "la banque");
    }
    this->current_cell = new_cell;
}
Cell* Player::processMove(int n, Board &board) {
    // Calcul of the new Cell idx
    int new_cell_idx = this->current_cell->getPosition() + n;
    // If the new idx is greater than the board size then we are on the start_cell and we receive money
    if (new_cell_idx >= BOARD_SIZE) { this->receive(MONEY_START_CELL, "la banque"); }
    // set the new current_cell
    this->current_cell = board[new_cell_idx];
    return this->current_cell;
};



int Player::getIndexOnBoard() {return 1;} //current_cell->getPosition();}

void Player::setAdmin() {admin = true;}

bool Player::isAdmin() { return admin; }

bool Player::isItMe(ClientManager &client) const {
    return this->client == &client;
}

ClientManager *Player::getClient() const { return client; }

void Player::send(std::string &s) const { if ( client ) client->send(s); }
void Player::send(std::string &&s) const { if ( client ) client->send(s); }
std::string Player::getUsername() const { return client->getAccount()->getUsername(); }

bool Player::isCurrentlyPLaying() const { return currently_playing; }
void Player::setCurrentlyPlaying(bool playing) {currently_playing = playing;}


void Player::forcedPay(int amount) {
    bank_account.pay(amount);
    if ( bank_account.getMoney() < 0 ) { this->status = PLAYER_STATUS::BANKRUPT; }
}

bool Player::pay(int amount, bool forced) {
    if ( forced || bank_account.getMoney() >= amount ) { this->forcedPay(amount); return true; }
    getClient()->send("Vous n'avez pas assez d'argent ! (Achat refusé)");
    return false;
}

void Player::receive(int amount, std::string source) {
    bank_account.gain(amount);
    getClient()->send("Vous avez reçu " + std::to_string(amount) + "e de " + source);
}

void Player::move(Cell *cell, bool pass_by_start) {
    if (passedByStart(cell, pass_by_start)) {
        receive(200, "Banque");
    }
    current_cell = cell;
}

bool Player::passedByStart(Cell* cell, bool pass_by_start) {
    if (cell->getPosition() - current_cell->getPosition() <= 0 and pass_by_start) {
        return true;
    }
    return false;
}
Cell *Player::getCurrentCell() const { return current_cell; }

void Player::goToJail(Cell *cell) {
    move(cell, false);
    this->status = JAILED;
    this->rolls_in_prison = 0;
}

void Player::exitJail() { this->status = FREE; }

bool Player::isInJail() const { return (status == JAILED); }

int Player::getRollsInPrison() const { return rolls_in_prison; }

void Player::addRollInPrison() { rolls_in_prison++; }

void Player::resetRollInPrison() { this->rolls_in_prison = 0; }

int Player::hasGOOJCards() const { return (GOOJ_cards.size() > 0); }

void Player::looseGOOJCard(){
    JailCard* card = GOOJ_cards.back();
    this->GOOJ_cards.pop_back();
    card->setOwner(nullptr);
    client->send("Vous perdez votre carte prison suite à son utilisation.\n");
}

bool Player::hasRolled() const { return has_rolled; }

void Player::setRolled(bool rolled) {has_rolled = rolled;}

int Player::roll(Dice &dice) {
    setRolled(true);
    return dice.roll();
}

std::vector<Property*> Player::getAllProperties() const { return properties; }
std::vector<Company*> Player::getAllCompanies() const { return companies; }
std::vector<Station*> Player::getAllStations() const { return stations; }
std::vector<JailCard*> Player::getAllGOOJCards() const { return GOOJ_cards; }
int Player::getNumberOfStations() const { return stations.size(); }
int Player::getNumberOfCompanies() const { return companies.size(); }

bool Player::isInAuction() const {return currently_in_auction;}
void Player::auctionStart() {currently_in_auction = true;}

void Player::leaveAuction() {
    getClient()->send("Vous quittez l'enchère.");
    currently_in_auction = false;
}

void Player::clearAuction() {
    currently_in_auction = false;
}

//ne pas ajouter de méthodes pour payer dans ces méthodes, elles sont aussi utilisées pour les échanges
void Player::acquireProperty(Property &prop) {
    prop.setOwner(this);
    properties.push_back(&prop);
}

void Player::acquireCompany(Company &comp) {
    comp.setOwner(this);
    companies.push_back(&comp);
}

void Player::acquireStation(Station &station) {
    station.setOwner(this);
    stations.push_back(&station);
}

void Player::acquireGOOJCard(JailCard *jail_card) {
    jail_card->setOwner(this);
    GOOJ_cards.push_back(jail_card);
}

void Player::useGOOJCard() {
    this->status = PLAYER_STATUS::FREE;
    GOOJ_cards.pop_back();
}

/*
 * check what type of land it is (used for exchanges)
 */
void Player::acquireLand(Land *land) {
    Property* p = dynamic_cast<Property*>(land);
    if (p != nullptr) { acquireProperty(*p); return;}
    Company* c = dynamic_cast<Company*>(land);
    if (c != nullptr) { acquireCompany(*c); return;}
    Station* s = dynamic_cast<Station*>(land);
    if (s != nullptr) { acquireStation(*s); return;}
}

void Player::removeLand(Land *land){
    int index = 0;
    Property* p = dynamic_cast<Property*>(land);
    if (p != nullptr) {
        for (auto property : properties) {
            if (property == p) { properties.erase(properties.begin()+index); }
            index++;
        }
        return;
    }
    Company* c = dynamic_cast<Company*>(land);
    if (c != nullptr) {
        for (auto company : companies) {
            if (company == c) { companies.erase(companies.begin()+index); }
            index++;
        }
        return;
    }
    Station* s = dynamic_cast<Station*>(land);
    if (s != nullptr) {
        for (auto station : stations) {
            if (station == s) { stations.erase(stations.begin()+index); }
            index++;
        }
        return;
    }
}

void Player::removeProperty(Property* p) {
    for (auto property : properties) {
        if (property == p) { properties.erase(properties.begin()+index); }
        index++;
    }
}

void Player::removeStation(Station* s) {
    for (auto station : stations) {
        if (station == s) { stations.erase(stations.begin()+index); }
        index++;
    }
}

void Player::removeCompagnie(Company* c) {
    for (auto company : companies) {
        if (company == c) { companies.erase(companies.begin()+index); }
        index++;
    }
}

void Player::auctionMustStart() { auction_must_start = true; }
void Player::exchangeFromJail() { exchange_from_jail = true; }

PLAYER_STATUS Player::getStatus() { return status; }
void Player::setStatus(PLAYER_STATUS new_status) {
    std::cout << "PLAYER STATUS CHANGE" << std::endl;
    std::cout << this->getUsername() << " is now " << (int)new_status << std::endl;
    std::cout << "FREE=0, JAIL=1, BANKRUPT=2, LOST=3" << std::endl;
    status = new_status;
}

std::string Player::getAllPossession(){
    std::string ret_string = "";
    for (auto property : properties ) { ret_string += property->getName() + ":"; }
    for (auto company : companies ) { ret_string += company->getName() + ":"; }
    for (auto station : stations ) { ret_string += station->getName() + ":"; }
    return ret_string;
}

std::string Player::getAllPossessionMortgageable() {
    std::string ret_string = "";
    for ( auto property : properties ) { if ( !property->isMortgaged() && property->getLevel() == PROPERTY_LEVEL::EMPTY ) { ret_string += property->getName() + ":"; } }
    for ( auto company : companies ) { if ( !company->isMortgaged() ) { ret_string += company->getName() + ":"; } }
    for ( auto station : stations ) { if ( !station->isMortgaged() ) { ret_string += station->getName() + ":"; } }
    return ret_string;
}

std::string Player::getAllBuildableProperties() {
    std::string str = "";
    for ( auto property : this->getAllProperties() ) { if ( property->isBuildable(this) ) { str += property->getName() + ":"; } }
    return str;
}

std::string Player::getAllSellableBuildProperties() {
    std::string str = "";
    for ( auto property : getAllProperties() ) { if ( property->canSellBuilding(this) ) { str += property->getName() + ":"; } }
    return str;
}

std::string Player::getAllExchangeablePossession() {
    std::string str = "";
    for ( auto property : properties ) { if ( property->getLevel() == PROPERTY_LEVEL::EMPTY ) { str += property->getName() + ":"; } }
    for ( auto company : companies )  { str += company->getName() + ":"; }
    for ( auto station : stations )    { str += station->getName() + ":"; }
    return str;
}

BankAccount* Player::getBankAccount(){
    return &bank_account;
}
void Player::setBankruptingPlayer(Player* player){
    bankrupting_player = player;
}
Player* Player::getBankruptingPlayer(){
    return bankrupting_player;
}

int Player::getPosition() const { return this->current_cell->getPosition(); }

int Player::getMoney() const { return this->bank_account.getMoney(); }
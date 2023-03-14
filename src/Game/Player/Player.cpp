//
// Created by Joachim on 14/02/2023.
//

#include "Player.hpp"
#include "BankAccount.hpp"
#include "../Board/Board.hpp"
//#include "../../Server/ClientManager/ClientManager.hpp"

/*
void Player::payToExitPrison() {

    pay(50);
    status = FREE;

}
bool Player::useGetOutOfJailCard() {
    if (GOOJ_cards.size() > 0){
        GOOJ_cards.pop_back();
        status = FREE;
        return true;
    }
    return false;
}

bool Player::isMine(Property property) {
    //return (*this == property.owner);
    return true; //delete this line
}

//void Player::partakeInAuction(int auction) {} pas encore d'actualité

int Player::rollDice(Dice* dice) {
    return dice->roll();
}

void Player::leaveGame() {
    declareBankruptcy();
    //warn that player is leaving, somehow
}

void Player::play() {
    //tj pas compris à quoi ça servait, ça sert d'ailleurs à rien je pense après réflexion
    //je ne sais pas comment envoyer des possibilités en client, mais c'est probablement ce qu'il faut faire ici
}

void Player::setPosition(Cell *cell) {
    current_cell = cell;
}

bool Player::buyProperty() {
    //return pay(current_cell->getPropertyPrice()); //cette méthode n'est pas dans le SRD, mais devrais exister
    return true;
}


void Player::move(int distance) {
    //current_cell->getPosition(); //n'existe pas dans le SRD!
    //current_cell = Board().getCell(current_cell->getPosition()); //getCell n'est pas non plus dans le srd
}

//void Player::exchange(int negociation) {} pas encore possible à implémenter

//int Player::getProperties() {} //le ide boude, je ne comprends pas pq

//void Player::declareBankruptcy() {} pas encore possible à implémenter
*/
int Player::getIndexOnBoard() {return 1;} //current_cell->getPosition();}

void Player::setAdmin() {admin = true;}

bool Player::isAdmin() { return admin; }

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
    if (cell->getPosition() - current_cell->getPosition() < 0 and pass_by_start) {
        return true;
    }
    return false;
}
Cell *Player::getCurrentCell() { return current_cell; }

void Player::goToJail(Cell *cell) {
    move(cell, false);
    this->status = JAILED;
    this->rolls_in_prison =0;
    getClient()->send("-|-|-Vous allez en prison.-|-|-");
}

void Player::exitJail() { this->status = FREE; }

bool Player::isInJail() const { return (status == JAILED); }

int Player::getRollsInPrison() const { return rolls_in_prison; }

void Player::addRollInPrison() { rolls_in_prison++; }

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

void Player::leaveAuctionSilently() {
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

PLAYER_STATUS Player::getPlayerStatus() { return status; }
void Player::setPlayerStatus(PLAYER_STATUS new_status) { status = new_status; }

std::string Player::getStringOfAllProperties(){
    std::string ret_string = "\n";
    for (auto property : properties) {
        ret_string += " - ";
        ret_string += property->getName();
        ret_string += "\n";
    }
    for (auto company : companies){
        ret_string += " - ";
        ret_string += company->getName();
        ret_string += "\n";
    }
    for (auto station : stations){
        ret_string += " - ";
        ret_string += station->getName();
        ret_string += ".\n";
    }
    return ret_string;
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

int Player::getPosition() { return current_cell->getPosition(); }
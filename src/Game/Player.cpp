//
// Created by Joachim on 14/02/2023.
//

#include "Player.hpp"
#include "Dice.hpp"
#include "BankAccount.hpp"
#include "Board/Board.hpp"
#include "../Server/ClientManager/ClientManager.hpp"


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
int Player::getIndexOnBoard() {return 1;}//current_cell->getPosition();}

void Player::setAdmin() {admin = true;}

bool Player::isAdmin() {return admin;}

ClientManager *Player::getClient() { return client; }

bool Player::isCurrentlyPLaying() {return currently_playing;}
void Player::setCurrentlyPlaying(bool playing) {currently_playing = playing;}

bool Player::pay(int amount, bool forced = false) {
    if (forced){
        bank_account.pay(amount);
        //TODO checkBankrupt();
    }
    else {
        if (bank_account.getMoney() < amount){
            getClient()->send("Vous n'avez pas assez d'argent.");
            return false;
        }
        else {
            bank_account.pay(amount);
        }
    }
    return bank_account.pay(amount);
}

std::string Player::receive(int amount, std::string source) {
    bank_account.gain(amount); //TODO
    return source;
}

void Player::move(Cell &cell, bool pass_by_start = true) {
    if (passedByStart(cell, pass_by_start)) {
        getClient()->send("Recieved " + std::to_string(200) + "e from" + receive(200, "Banque"));
    }
    current_cell = cell;
}

bool Player::passedByStart(Cell &cell, bool pass_by_start) {
    if (cell.getPosition() - current_cell->getPosition() < 0 and pass_by_start) {
        return true;
    }
    return false;
}
Cell *Player::getCurrentCell() {
    return current_cell;
}

void Player::goToJail(Cell &cell) {
    move(cell, false);
    this->status = JAILED;
    this->rolls_in_prison =0;
    getClient()->send("Vous allez en prison.");
}

void Player::exitJail() {
    this->status = FREE;
}

bool Player::isInJail() {
    return (status == JAILED);
}

int Player::getRollsInPrison() {
    return rolls_in_prison;
}

void Player::addRollInPrison(){
    rolls_in_prison++;
};

int Player::hasGOOJCards(){ return GOOJ_cards.size>0();}

void Player::looseGOOJCard(){
    JailCard* card = GOOJ_cards.back();
    this->GOOJ_cards().pop_back();
    card.setOwner(nullptr);
    client->send("Vous perdez votre carte prison")
}

bool Player::hasRolled() {return has_rolled;}

void Player::rolled(bool rolled) {has_rolled = rolled;}

std::vector<Property *> Player::getAllProperties() {
    return properties;
}

int Player::getNumberOfStations() { return stations.size(); }

int Player::getNumberOfCompanies() { return companies.size(); }

bool Player::isInAuction() {return currently_in_auction;}

void Player::auctionStart() {currently_in_auction = true;}

void Player::leaveAuction() {current_cell = false;}

/*void Player::acquireLand(Land *land) {
    //todo rendre cette méthode moins moche
    land->playerPurchase(this);
    Property* p = dynamic_cast<Property*>(land);
    Station* s = dynamic_cast<Station*>(land);
    Company* c = dynamic_cast<Company*>(land);

    

    if (p != nullptr){
        properties.push_back(p);
    }
    else if (s != nullptr) {
        stations.push_back(s);
    }
    else if (c != nullptr){
        companies.push_back(c);
    }
    else {
        std::cout << "Could not purchase property" << std::endl;
    }
}*/

void Player::acquireProperty(Property prop) {
    properties.push_back(prop);
}

void Player::acquireCompany(Company comp) {
    companies.push_back(comp);
}

void Player::acquireStation(Station station) {
    stationsS.push_back(station);
}
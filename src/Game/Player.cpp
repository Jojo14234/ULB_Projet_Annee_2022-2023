//
// Created by Joachim on 14/02/2023.
//

#include "Player.hpp"
#include "Dice.hpp"
#include "BankAccount.hpp"
#include "Board/Board.hpp"


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

int Player::getId() {return id;}

bool Player::isCurrentlyPLaying() {return currently_playing;}
void Player::setCurrentlyPlaying(bool playing) {currently_playing = playing;}

bool Player::pay(int amount) {
    return bank_account.pay(amount);
}

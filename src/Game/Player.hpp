//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_PLAYER_HPP
#define INFO_F209_GR5_2022_PLAYER_HPP

#include "BankAccount.hpp"
#include "Cell.hpp"
#include "Property.hpp"
#include "PLAYER_STATUS.hpp"


class Player {

    BankAccount bank_account = BankAccount{STARTING_MONEY};
    Cell *current_cell;
    // cards: vector<JailCard> c'est quoi ce truc
    std::vector<*Property> properties;
    PLAYER_STATUS status = FREE;
    bool online = true;

    void inPrisonAction();
public:
    void play();
    void setPosition(Cell* cell);
    bool buyProperty(Property property);
    bool pay(int amount);
    bool useGetOutOfJailCard();
    void propertyAction(); //c'est quoi?
    bool isMine(Property property);
    //void partakeInAuction(Auction auction); classe Auction pas encore créée
    void rollDice


};


#endif //INFO_F209_GR5_2022_PLAYER_HPP

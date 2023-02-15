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


    void payToExitPrison();

    //use a GOOJ card, if available
    bool useGetOutOfJailCard();

    //exectues action based on current cell
    void propertyAction();


    bool isMine(Property property);


    //void partakeInAuction(Auction auction); classe Auction pas encore créée

    //rolls dice
    void rollDice(*Dice dice); //waiting for dice merge

    //quit game
    void leaveGame();

public:

    // what does this do?
    void play();

    //set player to specific cell
    void setPosition(Cell* cell);

    //pay for property and add property to properties
    bool buyProperty(Property property);

    //pay an amount of money, return false if not capable
    bool pay(int amount);

    //moves player depending on result from dice
    void move();

    //exectues exchange agreed to by the 2 players involved (should this be in this class?)
    void exchange(Negociation negociation); //requires modifications to Negociation class compared to what is discribed in srd


    void getProperties(); //ça fait quoi? c'est quoi le return type??

};


#endif //INFO_F209_GR5_2022_PLAYER_HPP

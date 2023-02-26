//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_PLAYER_HPP
#define INFO_F209_GR5_2022_PLAYER_HPP

#include <vector>

#include "BankAccount.hpp"
#include "Board/Obtainable/Cells/Cell.hpp"
#include "Board/Obtainable/Cards/JailCard.hpp"
#include "Board/Obtainable/Cells/Property.hpp"
#include "PLAYER_STATUS.hpp"
#include "Dice.hpp"
#include "../utils/Configs.hpp"

class Player {

    BankAccount bank_account = BankAccount{STARTING_MONEY};

    Cell *current_cell;

    int id;

    bool admin = false;

    bool currently_playing = false;

/*
    //std::vector<JailCard> GOOJ_cards; waiting for Hawen

    //std::vector<*Property> properties; waiting for Hawen

    PLAYER_STATUS status = FREE;

    bool online = true;

    void payToExitPrison();

    //use a GOOJ card, if available
    bool useGetOutOfJailCard();

    //exectues action based on current cell
    void propertyAction(); //nécessaire étant donné la méthode acton dans cell et ses enfants?


    bool isMine(Property property);


    //void partakeInAuction(Auction auction); //classe Auction pas encore créée

    //rolls dice
    int rollDice(Dice* dice); //waiting for dice merge

    //quit game
    void leaveGame();

public:

    // what does this do?
    void play();

    //set player to specific cell
    void setPosition(Cell* cell);

    //pay for property and add property to properties
    bool buyProperty();

    //pay an amount of money, return false if not capable
    bool pay(int amount);

    //moves player depending on result from dice
    void move(int distance);

    //exectues exchange agreed to by the 2 players involved (should this be in this class?)
    //void exchange(Negociation negociation); //requires modifications to Negociation class compared to what is discribed in srd


    //std::vector<*Property> getProperties(); waiting for Hawen

    void declareBankruptcy();
*/
public:
    int getIndexOnBoard();

    Player(int id) : id{id} {}

    void setAdmin();
    bool isAdmin();

    int getId();

    bool isCurrentlyPLaying();
    void setCurrentlyPlaying(bool playing);

    bool pay(int amount);
};


#endif //INFO_F209_GR5_2022_PLAYER_HPP

//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_PLAYER_HPP
#define INFO_F209_GR5_2022_PLAYER_HPP

#include <vector>
#include <string.h>

#include "BankAccount.hpp"
//#include "Board/Obtainable/Cells/Cell.hpp"
#include "Board/Obtainable/Cards/JailCard.hpp"
#include "Board/Obtainable/Cells/Land/Land.hpp"
#include "Board/Obtainable/Cells/Land/Property.hpp"
#include "Board/Obtainable/Cells/Land/Company.hpp"
#include "Board/Obtainable/Cells/Land/Station.hpp"


#include "PLAYER_STATUS.hpp"
#include "Dice.hpp"
#include "../utils/Configs.hpp"

class ClientManager;
class Cell;

class Player {

    BankAccount bank_account = BankAccount{STARTING_MONEY};

    Cell *current_cell;

    ClientManager *client;

    int rolls_in_prison = 0;

    bool admin = false;

    bool has_rolled = false;
    bool currently_playing = false;

    bool currently_in_auction;
    bool auction_must_start;
    bool exchange_from_jail = false;

    PLAYER_STATUS status = FREE;
    Player* bankrupting_player = nullptr;

    std::vector<JailCard*> GOOJ_cards;   //get out of jail cards
    std::vector<Property*> properties;
    std::vector<Company*> companies;
    std::vector<Station*> stations;

/*
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

    Player(ClientManager* client) : client{client} {}

    void setAdmin();
    bool isAdmin();

    ClientManager* getClient();

    bool isCurrentlyPLaying();
    void setCurrentlyPlaying(bool playing);

    bool pay(int amount, bool forced = false);
    void receive(int amount, std::string source);

    void move(Cell& cell, bool pass_by_start = true);

    bool passedByStart(Cell &cell, bool passed_by_start);

    Cell* getCurrentCell();

    void exitJail();
    void goToJail(Cell *cell);
    bool isInJail();

    int getRollsInPrison();
    void addRollInPrison();

    int hasGOOJCards();
    void looseGOOJCard();

    bool hasRolled();
    void rolled(bool rolled);

    std::vector<Property*> getAllProperties();
    std::vector<Company*> getAllCompanies();
    std::vector<Station*> getAllStations();
    std::vector<JailCard*> getAllGOOJCards();

    int getNumberOfStations();
    int getNumberOfCompanies();

    void leaveAuction();
    bool isInAuction();
    void auctionStart();


    void acquireProperty(Property &prop);

    void acquireCompany(Company &comp);

    void acquireStation(Station &station);

    void acquireGOOJCard(JailCard *jail_card);

    void acquireLand(Land* land);

    void auctionMustStart();

    void exchangeFromJail();

    PLAYER_STATUS getPlayerStatus();

    void setPlayerStatus(PLAYER_STATUS new_status);

    std::string getStringOfAllProperties();

    BankAccount* getBankAccount();

    void setBankruptingPlayer(Player* player);

    Player* getBankruptingPlayer();
};


#endif //INFO_F209_GR5_2022_PLAYER_HPP

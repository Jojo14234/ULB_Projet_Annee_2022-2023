//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_PLAYER_HPP
#define INFO_F209_GR5_2022_PLAYER_HPP

#include <vector>
#include <string.h>

#include "BankAccount.hpp"
//#include "Board/Obtainable/Cells/Cell.hpp"
#include "../Board/Board.hpp"
#include "../Board/Obtainable/Cards/JailCard.hpp"
#include "../Board/Obtainable/Cells/Land/Land.hpp"
#include "../Board/Obtainable/Cells/Land/Property.hpp"
#include "../Board/Obtainable/Cells/Land/Company.hpp"
#include "../Board/Obtainable/Cells/Land/Station.hpp"


#include "PLAYER_STATUS.hpp"
#include "../Dice/Dice.hpp"
#include "../../utils/Configs.hpp"
//#include "../../Server/ClientManager/ClientManager.hpp"


class ClientManager;
class Cell;
class Board;

class Player {

    BankAccount bank_account = BankAccount{STARTING_MONEY};

    Cell* current_cell;
    ClientManager* client;

    int rolls_in_prison = 0;
    int index = -1;
    bool admin = false;

    bool has_rolled = false;
    bool currently_playing = false;
    int build_level = 0;

    int money_debt = 0;

    bool exchange_from_jail = false;

    PLAYER_STATUS status = FREE;
    Player* player_to_refund = nullptr;

    std::vector<JailCard*> GOOJ_cards;   //get out of jail cards
    std::vector<Property*> properties;
    std::vector<Company*> companies;
    std::vector<Station*> stations;

public:

    Player(ClientManager* client, Cell* start_cell) : client{client} {current_cell = start_cell;}

    int processRollDice(Dice &dice);


    // SETTER
    void setAdmin();
    void setCurrentlyPlaying(bool playing);
    void setRolled(bool rolled);
    void setExchangeFromJail();
    void setStatus(PLAYER_STATUS new_status);
    void setPlayerToRefund(Player* player);
    void setIndex(int new_index);
    void setExitJail();





    // GETTER
    bool isAdmin() const;
    ClientManager* getClient() const;
    std::string getUsername() const;
    Cell* getCurrentCell() const;
    int getRollsInPrison() const;
    std::vector<Property*> getAllProperties() const;
    std::vector<Company*> getAllCompanies() const;
    std::vector<Station*> getAllStations() const;
    std::vector<JailCard*> getAllGOOJCards() const;
    int getNumberOfStations() const;
    int getNumberOfCompanies() const;
    PLAYER_STATUS getStatus();
    BankAccount* getBankAccount();
    int getPosition() const;
    int getMoney() const;
    Player* getPlayerToRefund();
    int getPatrimoine(bool is_fast_game);
    int getIndex() const;
    int getDebt() const;





    // CHECK
    bool isItMe(ClientManager &client) const;
    bool isCurrentlyPLaying() const;
    bool isInJail() const;
    int hasGOOJCards() const;
    bool hasRolled() const;
    bool isBankruptToPlayer() const;
    bool isBankrupt() const;





    // ABOUT client
    void send(std::string &s) const;
    void send(std::string &&s) const;


    // ABOUT bankAccount
    bool pay(int amount, bool forced = false);
    void receive(int amount, std::string source);


    // MOVEMENT
    void move(Cell* cell, bool pass_by_start = true);
    bool passedByStart(Cell* cell, bool passed_by_start);
    void goToJail(Cell *cell);

    Cell* processMove(int n, Board &board);
    void processMove(Cell* new_cell, bool gainMoneyIfPassByStart);



    // roll_in_prison
    void addRollInPrison();
    void resetRollInPrison();


    // OTHER
    void looseGOOJCard();
    void useGOOJCard();

    void resetDebt();

    int roll(Dice &dice);

    void increaseBuildLevel();
    int getBuildLevel();


    void acquireLand(Land* land);
    void acquireProperty(Property &prop);
    void acquireCompany(Company &comp);
    void acquireStation(Station &station);
    void acquireGOOJCard(JailCard *jail_card);

    void removeLand(Land* land);
    void removeProperty(Property* p);
    void removeStation(Station* s);
    void removeCompagnie(Company* c);

    // STRING
    std::string getAllPossession();
    std::string getAllPossessionMortgageable();
    std::string getAllPossessionLiftMortgageable();
    std::string getAllBuildableProperties(bool is_fast_game);
    std::string getAllSellableBuildProperties();
    std::string getAllExchangeablePossession();
    std::string rollInfos(Dice &dice);

    // NEW FUNCTION
    std::vector<Land*> getAllLand();



};


#endif //INFO_F209_GR5_2022_PLAYER_HPP

#pragma once

#include <SFML/Network.hpp>
#include <vector>

#include "../Utility/GameCode.hpp"
#include "../../../Game/Capitalist.hpp"
#include "../../../Game/Player/Player.hpp"
#include "../../../Utils/Config/Configs.hpp"
#include "../../../Game/Board/Obtainable/Cells/Land/Land.hpp"



class ClientManager;	// forward declaration


class GameServer {

	// The game
	Capitalist game;

	// Represent the game code
	GameCode code;
	
	// Client manager connected to the game
	std::vector<ClientManager*> clients;

	// if the game is running
	bool active = true;

    int maxPlayer;

public:
	
	GameServer(GameParameters parameters)
            : game{parameters}, maxPlayer{parameters.maxPlayers} { clients.reserve(parameters.maxPlayers); }

    // Send big string with infos in it.
    void sendStartData();
    void sendGameData();
    void sendBetterGameData();


    // GAME LOOP
    GameStats clientLoop(ClientManager &client);
    void clientTurn(ClientManager &client, Player* me);
    void checkAndManageBankruptcy(ClientManager& client, Player* me);


    // PROCESS
    // Start
    void processStart(ClientManager* client);

    // Roll
    void processRollDice(ClientManager&, Player* player);

    // Build / Destruct
    void processBuild(ClientManager &client, Player* player);
    void processSellBuild(ClientManager &client, Player *player);

    // Mortgage / lift
    void processMortgage(ClientManager &client, Player *player);
    void processLiftMortgage(ClientManager &client, Player *player);

    // Exchange
    void processAskExchange(ClientManager &client, Player *player);
    void processExchange(ClientManager &client, Player *player);

    // Auction
    void processAskAuction(ClientManager &client, Player *player);
    void processAskBid(ClientManager &client, Player *player);
    void processAuction(Player* player, Land* land);
    void participateAuction(ClientManager &client, Player *player);

    // Jail
    void processJail(ClientManager& client, Player *player);

    //Bankrupt
    void processBankruptByGame(Player *player);
    void processBankruptByPlayer(ClientManager &client, Player* player, Player* other);
    void processPayDebt(ClientManager &client, Player* player);
    void processBankrupt(ClientManager &client, Player* player);

    // Lost
    void processLost(ClientManager &client);


    // INFOS
    void clientJoinGameInfos(ClientManager &client);
    void playerBuildInfos(ClientManager &client);
    void playerSellBuildInfos(ClientManager &client);
    void playerMortgageInfos(ClientManager &client);
    void playerLiftMortgageInfos(ClientManager &client);
    void playerExchangeInfos(ClientManager &client);
    void playerInJailInfos(ClientManager &client);
    void playerDebtInfos(ClientManager &client, Player* player);


    // UTILITY
    void addPlayer(ClientManager &client);
    void removeClient(ClientManager* client);
    void connectClientToThisGame(ClientManager &client);
    Player* findMe(ClientManager &client);
    void suspectBankrupt(Player* player);
    GAME_QUERY_TYPE getGameQuery(ClientManager &client);

    // Updater
    void updateAllClients(std::string update);
    void updateAllClientsWithQuery(QUERY &&query, std::string update);
    void updateThisClientWithQuery(QUERY &&query, std::string update, ClientManager &client);

	// getter
	int getCode() const;
    Capitalist* getGame();
    Land* getLand(std::string &name);
    CardDeck* getDeck(std::string name);
    int getCurrentPlayerIndex();
    int getMaxPlayer() const {return this->maxPlayer;}
    int getNbConnectedClient() const {return this->clients.size();}

    // checker
	bool isCode(int other) const;

};
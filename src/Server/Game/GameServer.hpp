#ifndef _SERVER_GAME_SERVER_HPP
#define _SERVER_GAME_SERVER_HPP

#include <vector>

#include "GameCode.hpp"
#include "../../Game/Capitalist.hpp"
#include "../../utils/Configs.hpp"
#include "../../Game/Board/Obtainable/Cells/Land/Land.hpp"
#include "../../Game/Player/Player.hpp"
#include <SFML/Network.hpp>



class ClientManager;	// forward declaraction

class GameServer {

	// The game
	Capitalist game;

	// Represent the game code
	GameCode code;
	
	// Client manager connected to the game
	std::vector<ClientManager*> clients;

	// if the game is running
	bool active = true;

public:
	
	GameServer() { clients.reserve(MAX_NB_PLAYER);}

    // Send big string with infos in it.
    void sendStartData();
    void sendGameData();
    void sendBetterGameData();

    void clientsSizeData(ClientManager &client);

    // Player

    void client_has_join_the_game(ClientManager &client);

    int clientLoop(ClientManager &client);

    Player* findMe(ClientManager &client);

    void clientTurn(ClientManager &client, Player* me);

    void processRollDice(ClientManager&, Player* player);

    void processBuild(ClientManager &client, Player* player);

    void processAuction(ClientManager &client, Player* player);

    void processBankrupt(ClientManager &client, Player* player);

    void processStart(ClientManager* client);

    void processJail(ClientManager& client, Player *player);

    void playerInJailInfos(ClientManager &client);

    void playerBuildInfos(ClientManager &client);

    void processSellBuild(ClientManager &client, Player *player);

    void playerSellBuildInfos(ClientManager &client);

    void processMortgage(ClientManager &client, Player *player);

    void playerMortgageInfos(ClientManager &client);

    void processLiftMortgage(ClientManager &client, Player *player);

    void playerLiftMortgageInfos(ClientManager &client);

    void processExchange(ClientManager &client, Player *player);

    void playerExchangeInfos(ClientManager &client);









    // Getter
    GAME_QUERY_TYPE getGameQuery(ClientManager &client);


    //void clientBeforeRollLoop(ClientManager &client);
    void clientBankruptLoop(ClientManager &client);
    void clientAuctionLoop(ClientManager &client, LandCell* land_cell);
    void participateInAuction(ClientManager &client);
    void participateInExchange(ClientManager &client);
	// Add a client to the game 
	//void addClient(ClientManager* client);
    void removeClient(ClientManager* client);

	// GETTERS
	int getCode() const;
    Player* getPlayerByUsername(std::string &name);

    Capitalist* getGame();
	
	// VERIFIERS
	bool isCode(int other) const;

    void processGameQuery(ClientManager &client, GAME_QUERY_TYPE query);
    void processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query);

    void processEndTurn(ClientManager &client);
    void processDiceRoll(ClientManager &client);
    void processMortgageProperty(ClientManager &client);
    void processDemortgageProperty(ClientManager &client);
    void processExchange(ClientManager &client);
    void processBuildBuildings(ClientManager &client);
    void processSellBuildings(ClientManager &client);

    //add Player object to players vector in Capitalist
    void addPlayer(ClientManager &client);

    bool isClientAdmin(ClientManager &client);

    void updateAllClients(std::string update);
    void updateAllClientsWithQuery(QUERY &&query, std::string update);
    void updateThisClientWithQuery(QUERY &&query, std::string update, ClientManager &client);
    bool proposeExchange(Player& proposing_player, Player &proposed_to_player, Land *land, int amount);
    Land* getLand(std::string &name);
    void processBankruptcyToPlayer();


    /*
     * Rémy Test
     */


    void clientBeforeRollLoop(ClientManager &client);

    void connectClientToThisGame(ClientManager &client);

    void treeDouble(ClientManager& client);

    int getCurrentPlayerIndex();

};

#endif
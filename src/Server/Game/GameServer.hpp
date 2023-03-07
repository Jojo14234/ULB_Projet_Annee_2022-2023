#ifndef _SERVER_GAME_SERVER_HPP
#define _SERVER_GAME_SERVER_HPP

#include <vector>

#include "GameCode.hpp"
#include "../../Game/Capitalist.hpp"
#include "../../utils/Configs.hpp"
#include "../../Game/Board/Obtainable/Cells/Land/Land.hpp"
#include "../../Game/Player.hpp"


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

    void sendAllGameData();

	// Loop for the client
	void clientLoop(ClientManager &client);
    void clientBeforeRollLoop(ClientManager &client);
    void clientBankruptLoop(ClientManager &client);
    void clientAuctionLoop(ClientManager &client, LandCell* land_cell);
    void participateInAuction(ClientManager &client);
	// Add a client to the game 
	void addClient(ClientManager* client);

	// GETTERS
	int getCode() const;
    Player* getPlayerByUsername(std::string &name);

    Capitalist* getGame();
	
	// VERIFIERS
	bool isCode(int other) const;

    void processGameQuery(ClientManager &client, GAME_QUERY_TYPE query);
    void processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query);

    void processStart(ClientManager &client);
    void processEndTurn(ClientManager &client);
    void processDiceRoll(ClientManager &client);
    void processMortgageProperty(ClientManager &client);
    void processExchange(ClientManager &client);
    void processBuildBuildings(ClientManager &client);
    void processSellBuildings(ClientManager &client);

    //add Player object to players vector in Capitalist
    void addPlayer(ClientManager &client);

    bool isClientAdmin(ClientManager &client);

    void updateAllClients(std::string update);
    bool proposeExchange(Player& proposing_player, Player &proposed_to_player, Land *land, int amount);
    Land* getLandByName(std::string &name);
    void processBankruptcyToPlayer(ClientManager &client);
};

#endif
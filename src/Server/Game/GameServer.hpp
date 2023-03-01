#ifndef _SERVER_GAME_SERVER_HPP
#define _SERVER_GAME_SERVER_HPP

#include <vector>

#include "GameCode.hpp"
#include "../../Game/Capitalist.hpp"
#include "../../utils/Configs.hpp"


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
	
	GameServer() { clients.reserve(MAX_NB_PLAYER); }

	// Loop for the client
	void clientLoop(ClientManager &client);

	// Add a client to the game 
	void addClient(ClientManager* client);

	// GETTERS
	int getCode() const { return code.getCode(); }
	
	// VERIFIERS
	bool isCode(int other) const { return code.getCode() == other; }

    void processGameQuery(ClientManager &client, GAME_QUERY_TYPE query);

    void processStart(ClientManager &client);
    void processEndTurn(ClientManager &client);
    void processDiceRoll(ClientManager &client);

    //add Player object to players vector in Capitalist
    void addPlayer(ClientManager &client) {this->game.addPlayer(client);}

    bool isClientAdmin(ClientManager &client) {return (game.getPlayerByClient(client)->isAdmin());}

    void updateAllClients(std::string& update) {
        for (auto client : clients){
            client->send(update);
        }
    }

};

#endif
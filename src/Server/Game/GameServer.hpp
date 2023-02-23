#ifndef _GAME_SERVER_HPP
#define _GAME_SERVER_HPP

#include <vector>

#include "GameCode.hpp"
#include "../../Game/Player.hpp"
#include "../../Game/Capitalist.hpp"
#include "../../utils/Configs.hpp"


class ClientManager;	// forward declaraction

class GameServer {

	Capitalist game;
	GameCode code;
	std::vector<ClientManager*> clients;
	bool active = true;

public:
	
	GameServer() { clients.reserve(MAX_NB_PLAYER); }

	// Loop for the client
	void clientLoop(ClientManager &client);

	// Add a client to the game 
	void addClient(ClientManager* client);

	// GETTERS
	int getCode() const { return code.getCode(); }
	
	bool isCode(int other) const { return code.getCode() == other; }

    void processGameQuery(ClientManager &client, GAME_QUERY_TYPE query);

    void processStart(ClientManager &client);
    void processEndTurn(ClientManager &client);

    //add Player object to players vector in Capitalist
    void addPlayer(int id) {this->game.addPlayer(id);}
    Player* getLinkedPlayer(ClientManager &client);


    };

#endif

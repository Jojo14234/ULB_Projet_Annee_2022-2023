#ifndef _GAME_SERVER_HPP
#define _GAME_SERVER_HPP

#include <vector>

#include "GameCode.hpp"
#include "../../Game/Capitalist.hpp"
#include "../../utils/Configs.hpp"
//#include "../ClientManager/ClientManager.hpp"


class ClientManager;	// forward declaraction

class GameServer {

	Capitalist game;
	GameCode code;
	std::vector<ClientManager*> clients;

public:
	
	GameServer() { clients.reserve(MAX_NB_PLAYER); }

	// Loop for the client
	void clientLoop(ClientManager &client);

	// Add a client to the game 
	void addClient(ClientManager* client) { this->clients.push_back(client); client->setGameServer(this); }

	// GETTERS
	int getCode() const { return code.getCode(); }
	
	bool isCode(int other) const { return code.getCode() == other; }

};

#endif

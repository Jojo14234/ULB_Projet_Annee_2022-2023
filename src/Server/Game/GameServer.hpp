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

};

#endif
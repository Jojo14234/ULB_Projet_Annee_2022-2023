#ifndef _GAME_SERVER_HPP
#define _GAME_SERVER_HPP

#include "../../Game/Capitalist.hpp"
//#include "../ClientManager/ClientManager.hpp"

class ClientManager;	// forward declaraction

class GameServer {

	Capitalist game;

public:

	GameServer()=default;

	// Loop for the client
	void clientLoop(ClientManager &client);
	
};

#endif
#pragma once

#include "GameServer.hpp"
#include "../../ClientManager/ClientManager.hpp"
#include "../../../Utils/List.hpp"

class GameServerList : public List<GameServer> {

public:

	using List<GameServer>::List;

	// To create a game and return its code
	int createGame(ClientManager* client, GameParameters parameters);

	// To make a client join a game by its code
	bool joinGame(ClientManager* client, int code);

    void removeGameServer(int gc);

};

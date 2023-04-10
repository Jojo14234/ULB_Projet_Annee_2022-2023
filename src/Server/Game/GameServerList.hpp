#ifndef _SERVER_GAME_SERVER_LIST_HPP
#define _SERVER_GAME_SERVER_LIST_HPP

#include "../../utils/List.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "GameServer.hpp"


class GameServerList : public List<GameServer> {

public:

	using List<GameServer>::List;

	// To create a game and return its code
	int createGame(ClientManager* client, bool fast);

	// To make a client join a game by its code
	bool joinGame(ClientManager* client, int code);

    void removeGameServer(int gc);

};

#endif
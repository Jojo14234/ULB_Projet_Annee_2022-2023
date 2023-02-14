#ifndef _GAME_SERVER_LIST_HPP
#define _GAME_SERVER_LIST_HPP

#include "../../utils/List.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "GameServer.hpp"


class GameServerList : public List<GameServer> {

public:

	using List<GameServer>::List;

	// To create a game and return its code
	int createGame(ClientManager* client);

	// To make a client join a game by its code
	bool joinGame(ClientManager* client, int code);

};

#endif

#include "GameServerList.hpp"
#include "GameServer.hpp"


int GameServerList::createGame(ClientManager* client) {
	GameServer &gs = this->emplace_back();
	gs.addClient(client);
	return gs.getGameCode();
}


bool GameServerList::joinGame(ClientManager* client, int code) {

}


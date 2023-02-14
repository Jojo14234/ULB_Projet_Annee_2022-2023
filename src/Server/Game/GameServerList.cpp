#include "GameServerList.hpp"


int GameServerList::createGame(ClientManager* client) {
	this->emplace_back();
	return this->back()->getGameCode();
}


bool GameServerList::joinGame(ClientManager* client, int code) {

}


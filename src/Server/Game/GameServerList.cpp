#include "GameServerList.hpp"
#include "GameServer.hpp"


int GameServerList::createGame(ClientManager* client) {
	std::shared_ptr<GameServer> gs = this->emplace_back(new GameServer());
    gs->connectClientToThisGame(*client);
	return gs->getCode();
}

bool GameServerList::joinGame(ClientManager* client, int code) {
	for (auto &gs : *this) {
		if (gs->isCode(code)) { gs->connectClientToThisGame(*client); return true; }
	} return false;
}

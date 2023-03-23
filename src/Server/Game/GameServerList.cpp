#include "GameServerList.hpp"
#include "GameServer.hpp"


int GameServerList::createGame(ClientManager* client, bool fast) {
	std::shared_ptr<GameServer> gs = this->emplace_back(new GameServer());
    gs->getGame()->setFastGame(fast);
    gs->connectClientToThisGame(*client);
	return gs->getCode();
}

bool GameServerList::joinGame(ClientManager* client, int code) {
	for (auto &gs : *this) {
		if (gs->isCode(code)) { gs->connectClientToThisGame(*client); return true; }
	} return false;
}

void GameServerList::removeGameServer(int gc) {
    for (auto game : *this) {
        if (game->isCode(gc)) {
            /*TODO remove gameServer*/
        }
    }
}
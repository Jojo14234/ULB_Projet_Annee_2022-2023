#include "GameServerList.hpp"
#include "GameServer.hpp"


int GameServerList::createGame(ClientManager* client, GameParameters parameters) {
	std::shared_ptr<GameServer> gs = this->emplace_back(new GameServer{parameters});
    gs->getGame()->setFastGame(parameters.isFastGame);
    gs->connectClientToThisGame(*client);
	return gs->getCode();
}

bool GameServerList::joinGame(ClientManager* client, int code) {
	for (auto &gs : *this) {
		if (gs->isCode(code) and gs->getMaxPlayer() > gs->getNbConnectedClient() and ! gs->getGame()->isRunning()) { gs->connectClientToThisGame(*client); return true; }
	} return false;
}

void GameServerList::removeGameServer(int gc) {
    for (auto game : *this) {
        if (game->isCode(gc)) {
            /*TODO remove gameServer*/
        }
    }
}
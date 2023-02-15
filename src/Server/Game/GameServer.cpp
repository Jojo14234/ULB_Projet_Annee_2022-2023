#include "GameServer.hpp"
#include "../ClientManager/ClientManager.hpp"


void GameServer::clientLoop(ClientManager &client) {
	client.inGame();
}

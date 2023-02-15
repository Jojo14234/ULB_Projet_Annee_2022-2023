#include "GameServer.hpp"
#include "../ClientManager/ClientManager.hpp"


void GameServer::clientLoop(ClientManager &client) {
	client.inGame();
}

void GameServer::addClient(ClientManager* client) {
	this->clients.push_back(client);
	client->setGameServer(this);
}

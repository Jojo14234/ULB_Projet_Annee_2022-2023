#include "GameServer.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"


void GameServer::clientLoop(ClientManager &client) {
	std::cout << client.getAccount()->getUsername() << " has join a game with code : " << this->code.getCode() << std::endl;
	while (this->active) {
		GAME_QUERY_TYPE query;
		client.receive(query);
		std::cout << "Receive: " << (int)query << " from client: " << client.getSocket().getRemoteAddress() << std::endl;
		game.send(query);
		std::string output;
		game.receive(output);
		client.send(output);
		if (query == GAME_QUERY_TYPE::LEAVE) { break; }
	}
	std::cout << client.getAccount()->getUsername() << " has left a game with code : " << this->code.getCode() << std::endl;
}

void GameServer::addClient(ClientManager* client) {
	this->clients.push_back(client);
	client->setGameServer(this);
}

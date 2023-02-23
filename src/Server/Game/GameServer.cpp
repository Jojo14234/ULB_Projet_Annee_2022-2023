#include "GameServer.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"


void GameServer::clientLoop(ClientManager &client) {
	std::cout << client.getAccount()->getUsername() << " has join a game with code : " << this->code.getCode() << std::endl;
	while (this->active) {
		GAME_QUERY_TYPE query;
		sf::Packet packet;
		// receive from client
		client.receive(query, packet);
		std::cout << "Receive: " << (int)query << " from client: " << client.getSocket().getRemoteAddress() << std::endl;

        // call capitalist methods
        processGameQuery(client, query);

		game.receiveQuery(query, packet);
		std::string output;
		game.sendMessage(output);
        game.displayGameStatus(); //temporary
		// send to client
		client.send(output);
		if (query == GAME_QUERY_TYPE::LEAVE) { break; }
	}
	std::cout << client.getAccount()->getUsername() << " has left a game with code : " << this->code.getCode() << std::endl;
}

void GameServer::addClient(ClientManager* client) {
	this->clients.push_back(client);
	client->setGameServer(this);
}
void GameServer::processGameQuery(ClientManager &client, GAME_QUERY_TYPE query){
    switch (query) {
        case GAME_QUERY_TYPE::START: processStart(client); break;
    }
}
void GameServer::processStart(ClientManager &client) {
    this->game.startGame();
    std::string response = "";
    response += "La partie est lancée!";
    client.send(response);


}

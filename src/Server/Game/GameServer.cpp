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
		//std::string output;
		//game.sendMessage(output);
        //game.displayGameStatus(); //temporary
		// send to client
		//client.send(output);
		if (query == GAME_QUERY_TYPE::LEAVE) { break; }
	}
	std::cout << client.getAccount()->getUsername() << " has left a game with code : " << this->code.getCode() << std::endl;
}

void GameServer::addClient(ClientManager* client) {
	this->clients.push_back(client);
	client->setGameServer(this);
}
void GameServer::processGameQuery(ClientManager &client, GAME_QUERY_TYPE query){
    if (GAME_QUERY_TYPE::START == query) processStart(client);
    else {
        if (client.getAccount()->getId() == game.getCurrentPlayer()->getId()){
            switch(query){
                case GAME_QUERY_TYPE::END_TURN: processEndTurn(client);
            }
        }
        else {
            client.send("Vous ne pouvez pas encore jouer étant donné que ça n'est pas votre tour.");
        }
    }

}
void GameServer::processStart(ClientManager &client) {
    if (!game.isRunning()){
        std::string response = "";
        if (getLinkedPlayer(client)->isAdmin()){
            this->game.startGame();
            client.send("La partie est lancée!");
        }
        else {
            client.send("Vous n'êtes pas administateur, demandez à l'administateur de lancer la partie.");
        }
    }
    else {
        client.send("La partie est déjà en cours.");
    }
}

void GameServer::processEndTurn(ClientManager &client) {
    game.endCurrentTurn();
    client.send("Votre tour est maintenant terminé.");
}

Player* GameServer::getLinkedPlayer(ClientManager &client){
    return game.getPlayerByClientId(client.getAccount()->getId());
}
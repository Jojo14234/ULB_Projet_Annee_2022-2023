#include "GameServer.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"
#include "string.h"


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
        if (&client == game.getCurrentPlayer()->getClient()){
            switch(query){
                case GAME_QUERY_TYPE::END_TURN: processEndTurn(client); break;
                case GAME_QUERY_TYPE::ROLL_DICE: processDiceRoll(client); break;
            }
        }
        else {
            client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour.");
        }
    }
}
void GameServer::processStart(ClientManager &client) {
    if (!game.isRunning()){
        if (isClientAdmin(client)){
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

void GameServer::processDiceRoll(ClientManager &client) {
    std::string output = "";
    output += "You rolled a " + std::to_string(game.rollDice()); //should technically have a method for this in capitalist, but flemme
    if (game.rolledADouble()){
        output += " and it's a double!";
    }
    client.send(output);
}

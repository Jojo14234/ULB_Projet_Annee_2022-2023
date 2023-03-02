#include "GameServer.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"
#include "string.h"


void GameServer::clientLoop(ClientManager &client) {
	std::cout << client.getAccount()->getUsername() << " has join a game with code : " << this->code.getCode() << std::endl;
	while (this->active) {
		GAME_QUERY_TYPE query;
		sf::Packet packet;

        // if player is in jail
        if (game.getCurrentPlayer()->isInJail()){
            game.getCurrentPlayer()->getCurrentCell()->action(game.getCurrentPlayer());
        }
        else {
            clientBeforeRollLoop(client);
        //after roll loop
    }
        //bankrupcy loop
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

void GameServer::clientBeforeRollLoop(ClientManager &client) {
    while (true) {
        GAME_QUERY_TYPE query;
        sf::Packet packet;
        client.receive(query);
        if (&client == game.getCurrentPlayer()->getClient()){
            if (GAME_QUERY_TYPE::START == query) processStart(client);
            else if (game.isRunning()){
                if (&client == game.getCurrentPlayer()->getClient()){
                    processGameQueryBeforeRoll(client, query);
                }
                else {
                    client.send("Ce n'est pas encore votre tour.");
                }
            }
            else {
                client.send("La partie n'est pas encore lancée.");
            }
        }
        else {
            client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour.");
        }
    }
}

void GameServer::addClient(ClientManager* client) {
	this->clients.push_back(client);
	client->setGameServer(this);
}

/* OBSOLETE
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
*/

void GameServer::processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query) {
    switch (query) {
        case GAME_QUERY_TYPE::END_TURN: processEndTurn(client); break;
        case GAME_QUERY_TYPE::ROLL_DICE: processDiceRoll(client); break;
        default: client.send("Cette commande n'est pas disponible.");
    }
}

void GameServer::clientBankruptLoop(ClientManager &client) {
    //TODO
}

void GameServer::processStart(ClientManager &client) {
    if (!game.isRunning()){
        if (isClientAdmin(client)){
            if (game.getNumberOfPlayers() > 1){
                this->game.startGame();
                client.send("La partie est lancée!");
            }
            else {
                client.send("Vous êtes seul dans la partie, invitiez un autre joueur pour lancer la partie.");
            }
        }
        else {
            client.send("Vous n'êtes pas administateur.");
        }
    }
    else {
        client.send("La partie est déjà en cours.");
    }
}

void GameServer::processEndTurn(ClientManager &client) {
    if (game.getCurrentPlayer()->hasRolled() and !game.getCurrentPlayer()->isInJail()){
        game.endCurrentTurn();
        client.send("Votre tour est maintenant terminé.");
    }
    client.send("Vous devez jeter les dés avant de finir votre tour.");
}

void GameServer::processDiceRoll(ClientManager &client) {
    while (game.getDice()->getDoubleCounter() != 2){
        std::string output = "";
        output += std::string(client.getAccount()->getUsername()) + " rolled a " + std::to_string(game.rollDice()); //should technically have a method for this in capitalist, but flemme
        if (game.rolledADouble()){
            output += " and it's a double, he/she will play again!";
        }
        updateAllClients(output);
        game.getCurrentPlayer()->getClient()->send(output);
        game.getCurrentPlayer()->move(game.getBoard().getCellByIndex((game.getCurrentPlayer()->getCurrentCell()->getPosition() + game.getDice()->getResults()) % BOARD_SIZE));

        game.getCurrentPlayer()->getCurrentCell()->action(game.getCurrentPlayer());

        if (!game.getDice()->isDouble()) { break; }
    }
    game.getCurrentPlayer()->rolled(true);
    if (game.getDice()->getDoubleCounter() == 2) {
        game.getCurrentPlayer()->goToJail(game.getBoard()->getCellByIndex(PRISON_INDEX));
    }
}


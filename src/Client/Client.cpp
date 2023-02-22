#include <iostream>
#include <string>
#include <stdlib.h>     /* strtol */
#include <SFML/Network.hpp>

#include "AuthentificationManager.hpp"
#include "../utils/Configs.hpp"
#include "../utils/Exceptions.hpp"
#include "Client.hpp"
#include "InputParser/MainInputParser.hpp"
#include "InputParser/GameInputParser.hpp"


// Public

void Client::mainLoop() {
	while (true) {
		this->ui.connexionMsg();
		while (not this->connectedToAnAccount) {
			// Si l'utilisateur à fait /disconnect dans le menu de connexion, cela ferme l'application
			if (!this->connectionLoop()) { return; }
		}
		while (this->connectedToAnAccount) {
			MainInputParser parser = this->controller.getNewParsedInput();
			if (parser.getQueryType() == QUERY_TYPE::NONE) { continue; }
			this->sendToServer(parser);
			std::string output;
			this->receiveFromServer(output);
			output = this->analyseServerResponse(output);
			if (output == "GAME" or parser.getQueryType() == QUERY_TYPE::CREATE_GAME) { this->inGame = true; this->gameLoop(); }
			else { std::cout << output << std::endl; }
		}
	}
}


// Private

void Client::connectToServer() {
	if (this->socket.connect(IP, PORT) != sf::Socket::Done) {
		throw ConnectServerClientException();
	}
}

void Client::disconnectFromServer() {
	this->sendToServer(MainInputParser{"/disconnect"});
	std::string output;
	this->receiveFromServer(output);
	this->ui.disconnect();
}

void Client::sendToServer(const MainInputParser &input) {
	sf::Packet packet;
	packet << static_cast<int>(input.getQueryType());
	switch(input.getQueryType()) {
		case QUERY_TYPE::JOIN_GAME : packet << stoi(input[1]); break;
		
		case QUERY_TYPE::REGISTER :	// same as under
		case QUERY_TYPE::LOGIN :    // same as under
		case QUERY_TYPE::MESSAGE_SEND : packet << input[1] << input[2]; break;
		
		case QUERY_TYPE::MESSAGE_SHOW :  // same as under
		case QUERY_TYPE::FRIENDS_ACCEPT: // same as under
		case QUERY_TYPE::FRIENDS_REFUSE: // same as under
		case QUERY_TYPE::FRIENDS_ADD:    // same as under
		case QUERY_TYPE::FRIENDS_REMOVE: packet << input[2]; break;

		default : break;
	}
	if (this->socket.send(packet) != sf::Socket::Done) { throw WritePipeClientException(); }
}

void Client::sendToServer(const GameInputParser &input) {
	sf::Packet packet;
	packet << static_cast<int>(input.getQueryType());
	switch(input.getQueryType()) {
		
		case GAME_QUERY_TYPE::ARG1 : packet << input[1]; break;
		case GAME_QUERY_TYPE::ARG2 : packet << input[1] << input[2]; break;
		
		default : break;
	}
	if (this->socket.send(packet) != sf::Socket::Done) { throw WritePipeClientException(); }
}

void Client::receiveFromServer(std::string &output) {
	sf::Packet packet;
	if (this->socket.receive(packet) != sf::Socket::Done) { throw ReadPipeClientException(); }
	packet >> output;
}

bool Client::checkAccountConnection(std::string &output, QUERY_TYPE query) {
	if (output == "TRUE") {
		(query == QUERY_TYPE::REGISTER) ? this->ui.acceptRegister() : this->ui.acceptLogin();
		return true;
	}
	(query == QUERY_TYPE::REGISTER) ? this->ui.refuseRegister() : this->ui.refuseLogin();
	return false;
}

std::string Client::analyseServerResponse(std::string &output) {
	if (output == "DISCONNECT") {
		this->connectedToAnAccount = false;
		return "Déconnexion de votre compte";
	}
	else if (output[0] == '1' && output[1] == '.') {
		return output + "Fin du classement";
	}
	else {
		return output;
	}
}

bool Client::connectionLoop() {
	MainInputParser parser = this->controller.getNewParsedInput();
	QUERY_TYPE query = parser.getQueryType();

	if ((query == QUERY_TYPE::REGISTER || query == QUERY_TYPE::LOGIN) && parser.getNbParameters() == 2) {
		//check la taille du pseudo et du mdp
		AuthentificationManager authentication{parser[1], parser[2]};
		authentication.showErrorMessage(ui);
		if (!authentication.isValid()) { return true; }
		//envoyer au serveur pour check dans la db
		this->sendToServer(parser);
		std::string output;
		this->receiveFromServer(output);
		connectedToAnAccount = this->checkAccountConnection(output, query);
	}
	//L'utilisateur souhaite quitter l'application
	else if (query == QUERY_TYPE::DISCONNECT) {this->disconnectFromServer(); return false;}
	//L'utilisateur a rentré une mauvaise commande
	else { this->ui.badConnexionInput(); }
	return true;
}

void Client::gameLoop() {
	std::cout << "Vous entrez dans une partie" << std::endl;
	while(this->inGame) {
		GameInputParser parser = this->controller.getNewGameParsedInput();
		if (parser.getQueryType() == GAME_QUERY_TYPE::NONE) { continue; }
		this->sendToServer(parser);
		std::string output;
		this->receiveFromServer(output);
		if(output == "ENDGAME") { this->inGame = false; }
		else { std::cout << output << std::endl; }
	}
	std::cout << "Vous quitez la partie" << std::endl;
}

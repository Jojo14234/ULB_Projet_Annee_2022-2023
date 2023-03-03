#include <iostream>
#include <string>
#include <SFML/Network.hpp>
#include <thread>

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
		while (not this->connected_to_an_account) {
			// If the user want to quit
			if (!this->connectionLoop()) { return; }
		}
		while (this->connected_to_an_account) {
			MainInputParser parser = this->controller.getNewParsedInput();
			// if bad input format
			if (parser.getQueryType() == QUERY_TYPE::NONE) { continue; }
			// send the input to the server
			this->sendToServer(parser);
			std::string output;
			// wait the response from the server
			this->receiveFromServer(output);
			output = this->analyseServerResponse(output);
			// If need to enter the game loop
			if (output == "GAME" or parser.getQueryType() == QUERY_TYPE::CREATE_GAME) { this->in_game = true; this->gameLoop(); }
			else { std::cout << output << std::endl; }
		}
	}
}


// Private

void Client::connectToServer() {
	if (this->socket.connect(IP, PORT) != sf::Socket::Done) {
		throw ConnectServerClientException();	// can't connect to the server
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
	if (this->socket.send(packet) != sf::Socket::Done) {
		throw WritePipeClientException(); // can't write on the socket
	}
}

void Client::sendToServer(const GameInputParser &input) {
	sf::Packet packet;
	packet << static_cast<int>(input.getQueryType());
	switch(input.getQueryType()) {
		
		case GAME_QUERY_TYPE::ARG1 : packet << input[1]; break;
		case GAME_QUERY_TYPE::ARG2 : packet << input[1] << input[2]; break;
        case GAME_QUERY_TYPE::BID : packet << input[1]; break;
        case GAME_QUERY_TYPE::SELECT : packet << input[1]; break;
		default : break;
	}
	if (this->socket.send(packet) != sf::Socket::Done) {
		throw WritePipeClientException();  // can't write on the socket
	}
}

void Client::receiveFromServer(std::string &output) {
	sf::Packet packet;
	if (this->socket.receive(packet) != sf::Socket::Done) {
		throw ReadPipeClientException();  // can't read on the socket
	} packet >> output;
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
		this->connected_to_an_account = false;	// disconnect from the account
		return "Déconnexion de votre compte";
	} else if (output[0] == '1' && output[1] == '.') {
		return output + "Fin du classement";
	} else { return output; }
}

bool Client::connectionLoop() {
	MainInputParser parser = this->controller.getNewParsedInput();
	QUERY_TYPE query = parser.getQueryType();
	if ((query == QUERY_TYPE::REGISTER || query == QUERY_TYPE::LOGIN) && parser.getNbParameters() == 2) {
		// check the validity of the input
		AuthentificationManager authentication{parser[1], parser[2]};
		authentication.showErrorMessage(ui);
		if (!authentication.isValid()) { return true; }
		// send the input to the server
		this->sendToServer(parser);
		std::string output;
		// wait for response from the server
		this->receiveFromServer(output);
		this->connected_to_an_account = this->checkAccountConnection(output, query);
	}
	// if the user want to quit
	else if (query == QUERY_TYPE::DISCONNECT) {this->disconnectFromServer(); return false;}
	// if bad input
	else { this->ui.badConnexionInput(); }
	return true;
}

void Client::gameLoop() {
	std::cout << "Vous entrez dans une partie" << std::endl;
	std::thread send_thread(&Client::receiveFromServerLoop, this);
	this->sendToServerLoop();
	std::cout << "Vous quitez la partie" << std::endl;
}

void Client::sendToServerLoop() {
	while (this->in_game) {
		GameInputParser parser = this->controller.getNewGameParsedInput();
		if (parser.getQueryType() == GAME_QUERY_TYPE::NONE) { continue; }
		// send the input to the server
		this->sendToServer(parser);
	}
}

void Client::receiveFromServerLoop() {
	while (this->in_game) {
		std::string output;
		// wait the response from the server
		this->receiveFromServer(output);
		// if the game is finished
		if(output == "ENDGAME") { this->in_game = false; }
		else { std::cout << output << std::endl; }
	}
}

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "../utils/Configs.hpp"
#include "../utils/Exceptions.hpp"
#include "./Message/Message.hpp"
#include "Client.hpp"
#include "InputParser.hpp"


// Public

void Client::mainLoop() {
    while (true) {
        // WELCOME MESSAGE
        Message msg;
        msg.connexionMsg();
        while (!connectToAccount) {
            // Try to connect
            if (!this->connexionLoop()) { return; }
        }
        std::cout << "You are now connected to your account !" << std::endl;
        while (connectToAccount) {
            // Get input
            std::string input;
            std::cout << ">";
            std::getline(std::cin, input);
            // Parse the input
            InputParser parser{input};
            // Send input to the server
            this->sendToServer(parser);
            // Receive a message (for now it just show it on stdout)
            std::string output;
            this->receiveFromServer(output);
            std::cout << "Received: " << output << std::endl;
            if (output == "Déconnexion") {connectToAccount = false; break;}
        }
    }
}


bool Client::connexionLoop() {
    // GET INPUT
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);

    // PARSE THE INPUT
    InputParser connexionInput{input};
    QUERY_TYPE query = connexionInput.getQueryType();

    // 2 POSSIBILIES IN CONNECTION MODE
    // #1 : /login || /register + username and password (2 args)
    if ((query == QUERY_TYPE::LOGIN || query == QUERY_TYPE::REGISTER) && connexionInput.getNbParameters() == 2) {
        this->sendToServer(connexionInput);
        connectToAccount = checkAccountConnexion(connexionInput.getQueryType());
    }
    // #2 : /disconnect (0 args)
    else if (query == QUERY_TYPE::DISCONNECT) {
        this->disconnectToServer();
        return false;
    }
    // #3 : BAD COMMAND
    else {
        Message msg;
        msg.badConnexionInput();
    }
    return true;
}

bool Client::checkAccountConnexion(QUERY_TYPE query) {
    std::string output;
    Message msg;
    this->receiveFromServer(output);
    // CONNECTION || CREATION ACCEPTED
    if (output == "TRUE") {return true;}
    // CREATION REFUSED
    if (query == QUERY_TYPE::REGISTER) {msg.refuseRegister();}
    // CONNECTION REFUSED
    else if (query == QUERY_TYPE::LOGIN) {msg.refuseLogin();}
    return false;
}


// Private

void Client::connectToServer() {
	if (this->socket.connect(IP, PORT) != sf::Socket::Done) {
		throw ConnectServerClientException();
	}
}

void Client::disconnectToServer() {
	this->sendToServer(InputParser{"/disconnect"});
}

void Client::sendToServer(const InputParser &input) {
	sf::Packet packet;
	packet << static_cast<int>(input.getQueryType());

	switch(input.getQueryType()) {

		case QUERY_TYPE::JOIN_GAME : packet << stoi(input[1]); break;
		case QUERY_TYPE::MESSAGE :	// same as under
		case QUERY_TYPE::LOGIN :    // same as under
		case QUERY_TYPE::REGISTER : packet << input[1] << input[2]; break;

		default : break;
	}
	if (this->socket.send(packet) !=  sf::Socket::Done) { throw WritePipeClientException(); }
}

void Client::receiveFromServer(std::string &output) {
	sf::Packet packet;
	if (this->socket.receive(packet) !=  sf::Socket::Done) { throw ReadPipeClientException(); }
	packet >> output;
}


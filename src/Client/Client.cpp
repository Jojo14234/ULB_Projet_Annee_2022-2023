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

        // Connection to an account
        while (!this->connected_to_an_account) {
            if (!this->connectionLoop()) { return; }
        }
        // ConnectionLoop returns false if the user want to quit the application
        // ConnectionLoop returns true if the user have not succeeded to log into it's account
        // The only way to know if the user is connected to its account is through the variable `connect_to_an_account`

        // When connected to an account
        while (this->connected_to_an_account) {
            MainInputParser parser = this->controller.getNewParsedInput();
            if (parser.getQueryType() == QUERY_TYPE::NONE) { continue; } // If the input is in a bad format, we just continue the loop

            std::string output;
            this->sendToServer(parser);     // send the input to the server
            QUERY query = this->receiveFromServer2(output);  // get the output from the server

            this->parseQuery(query, output); // Analyse the output
        }
    }
}

void Client::parseQuery(QUERY query, std::string output) {
    switch (query) {
        case QUERY::DISCONNECT : this->connected_to_an_account = false; showMsg("Déconnexion de votre compte"); break;
        case QUERY::RANKING : showMsg(output); break;
        case QUERY::PLAYER_JOIN_GAME : this->in_game = true; showMsg(output, query) ;this->gameLoop(); break;
        case QUERY::MESSAGE : showMsg(output);
        default : break;
    }
}

void Client::showMsg(std::string msg, QUERY query) {
    std::cout << "["<<(int)query<<"] " << msg << std::endl;
}


// Private

void Client::connectToServer() {
    // If it can't connect to the server, throws an error
    if (this->socket.connect(IP, PORT) != sf::Socket::Done) { throw ConnectServerClientException(); }
}

void Client::disconnectFromServer() {
    MainInputParser input{"/disconnect"};
	this->sendToServer(input);
	this->ui.disconnect();
}

void Client::sendToServer(MainInputParser &input) {
    // Create the packet
    sf::Packet packet;
    packet << static_cast<int>(input.getQueryType());

    switch(input.getQueryType()) {
        // Add only the first argument to the packet
        case QUERY_TYPE::JOIN_GAME : packet << stoi(input[1]); break;

            // Add both of the first and second arguments to the packet
        case QUERY_TYPE::REGISTER :
        case QUERY_TYPE::LOGIN :    packet << input[1] << input[2]; break;
        case QUERY_TYPE::MESSAGE_SEND : input.regroupParameters(2); packet << input[1] << input[2]; break;

            // Add only the second argument to the packet
        case QUERY_TYPE::MESSAGE_SHOW  :
        case QUERY_TYPE::FRIENDS_ACCEPT:
        case QUERY_TYPE::FRIENDS_REFUSE:
        case QUERY_TYPE::FRIENDS_ADD   :
        case QUERY_TYPE::FRIENDS_REMOVE: packet << input[2]; break;

        default : break;
    }
    // Throw an error if it can't write on the socket
    if (this->socket.send(packet) != sf::Socket::Done) { throw WritePipeClientException(); }
}

void Client::sendToServer(const GameInputParser &input) {
    // Create the packet
	sf::Packet packet;
	packet << static_cast<int>(input.getQueryType());

	switch(input.getQueryType()) {
        // Add only the first argument to the packet
		case GAME_QUERY_TYPE::ARG1   :
        case GAME_QUERY_TYPE::BID    :
        case GAME_QUERY_TYPE::SELECT : packet << input[1]; break;
        // Add both of the first and second arguments to the packet
        case GAME_QUERY_TYPE::TRADE  :
        case GAME_QUERY_TYPE::ARG2   : packet << input[1] << input[2]; break;
		default : break;
	}
    // Throw an error if it can't write on the socket
    if (this->socket.send(packet) != sf::Socket::Done) { throw WritePipeClientException(); }
}

void Client::receiveFromServer(std::string &output) {
    sf::Packet packet;
    // Throw an error if it can't read the socket
    if (this->socket.receive(packet) != sf::Socket::Done) { throw ReadPipeClientException(); }
    packet >> output; // Extract the content of the socket
}

QUERY Client::receiveFromServer2(std::string &output) {
    sf::Packet packet;
    int query;
    // Throw an error if it can't read the socket
    if (this->socket.receive(packet) != sf::Socket::Done) { throw ReadPipeClientException(); }
    packet >> query >> output; // Extract the content of the socket
    return static_cast<QUERY>(query);
}

bool Client::checkAccountConnection(QUERY output, QUERY_TYPE query) {
    // Show the right message on the screen in function of the connection output and the query
    if      (output == QUERY::FALSE and query == QUERY_TYPE::REGISTER)  { this->ui.refuseRegister(); }
    else if (output == QUERY::FALSE and query == QUERY_TYPE::LOGIN)     { this->ui.refuseLogin(); }
    else if (output == QUERY::TRUE and query == QUERY_TYPE::REGISTER) { this->ui.acceptRegister(); }
    else if (output == QUERY::TRUE and query == QUERY_TYPE::LOGIN)    { this->ui.acceptLogin(); }
    // Return whether or not the connection between the account and the client was made
    return output == QUERY::TRUE;
}

bool Client::connectionLoop() {
    MainInputParser parser = this->controller.getNewParsedInput();
    QUERY_TYPE query = parser.getQueryType();

    // User try to connect to its account
    if ( ( query == QUERY_TYPE::REGISTER || query == QUERY_TYPE::LOGIN ) && parser.getNbParameters() == 2 ) {

        //Check validity of the connections inputs
        AuthentificationManager authentication{parser[1], parser[2]};
        authentication.showErrorMessage(ui);         // Show error message if needed


        if (authentication.isValid()) {
            std::string output;
            this->sendToServer(parser);   // send the input to the server
            QUERY query1 = this->receiveFromServer2(output);// get the output from the server
            // Update the `connected_to_an_account` variable with the output from the server
            this->connected_to_an_account = this->checkAccountConnection(query1, query);
        }
        return true;
    }
    // User wants to quit the application
    else if ( query == QUERY_TYPE::DISCONNECT ) { this->disconnectFromServer(); return false; }
    // User has entered bad inputs
    else if ( query == QUERY_TYPE::NONE ) { this->ui.badConnexionInput(); return true; }
    // Other
    else { std::cout << "(Client::connectionLoop()) receive an untreated query [" << (int)query << "]" << std::endl; return true;}
}

void Client::gameLoop() {
    //std::cout << "Vous entrez dans une partie (Client.cpp client.gameLoop)" << std::endl;
    //this->in_game = true; //test
    std::thread send_thread(&Client::receiveFromServerLoop, this);
    this->sendToServerLoop();
    //this->in_game = false; //test
    std::cout << "Vous quittez la partie (Client.cpp client.gameLoop)" << std::endl;
}

void Client::sendToServerLoop() {
    // Loop while the client is in a game
    while (this->in_game) {
        GameInputParser parser = this->controller.getNewGameParsedInput();
        // If the input from the client is not unknown, it's sent to the server
        if (parser.getQueryType() != GAME_QUERY_TYPE::NONE) { this->sendToServer(parser); }
    }
}

void Client::receiveFromServerLoop() {
    while (this->in_game) {
        std::string output;
        QUERY query = this->receiveFromServer2(output); // get the output from the server
        if (query == QUERY::STOP_WAIT) {
            std::cout << "Received stop time exchange" << std::endl;
            this->sendToServer(GameInputParser{output});
        }
        if( query == QUERY::ENDGAME ) { this->in_game = false; } // If output is "ENDGAME" it should stop the loop.
        else { std::cout << output << std::endl; }
    }
}

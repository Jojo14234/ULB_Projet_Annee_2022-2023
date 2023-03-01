#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "InputParser/MainInputParser.hpp"
#include "ClientController.hpp"
#include "./UI/ConnectionUI.hpp"


class Client {

    sf::TcpSocket socket;
    
    bool connected_to_an_account = false;
    bool in_game = false;
    
    int account_id;

    ClientController controller;
    ConnectionUI ui;

    // Connect the client to the server
    void connectToServer();

    // Send to server a message to disconnect
    void disconnectFromServer();

    // Send a message to the server
    void sendToServer(const MainInputParser &input);
    void sendToServer(const GameInputParser &input);

    // Receive a message from the server
    void receiveFromServer(std::string &output);

    // If the account connection/creation is valid 
    bool checkAccountConnection(std::string &output, QUERY_TYPE query);

    // Analyse the server response and return what to print
    std::string analyseServerResponse(std::string &output);

    // Try to connect to an account
    bool connectionLoop();

    // Special loop if the client is in a game
    void gameLoop();

	// Send messages to the server
	void sendToServerLoop();

	// Receive messages from the server
	void receiveFromServerLoop();
    
public:

    Client() { this->connectToServer(); }
    
    // Main Loop of the client
    void mainLoop();

};

#endif

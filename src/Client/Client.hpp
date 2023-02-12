#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "InputParser.hpp"


class Client {

	sf::TcpSocket socket;

    bool connectToAccount = false;
	
	// Connect the client to the server
	void connectToServer();

	// Send to server a message to disconnect
	void disconnectToServer();

	// Send a message to the server
	void sendToServer(const InputParser &input);

	// Receive a message from the server
	void receiveFromServer(std::string &output);

    // Try to connect to an account
    bool connexionLoop();

	// If the account connection/creation is valid 
    bool checkAccountConnexion(QUERY_TYPE query);

public:

	Client() { this->connectToServer(); }

	// Main Loop of the client
	void mainLoop();

};

#endif

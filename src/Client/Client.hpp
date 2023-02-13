#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "InputParser.hpp"
#include "ClientController.hpp"
#include "./UI/ConnectionUI.hpp"


class Client {

    sf::TcpSocket socket;
    bool connectedToAnAccount = false;
    ClientController controller;
    ConnectionUI ui;

    // Connect the client to the server
    void connectToServer();

    // Send to server a message to disconnect
    void disconnectFromServer();

    // Send a message to the server
    void sendToServer(const InputParser &input);

    // Receive a message from the server
    void receiveFromServer(std::string &output);

    // If the account connection/creation is valid 
    bool checkAccountConnection(std::string &output, QUERY_TYPE query);

    // Try to connect to an account
    bool connectionLoop();

    std::string analyseServerResponse(std::string &output);

public:

    Client() { this->connectToServer(); }
    
    // Main Loop of the client
    void mainLoop();

};

#endif
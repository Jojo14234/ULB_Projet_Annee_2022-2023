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
    ClientController controller{};
    ConnectionUI ui{};

    void connectToServer();
    void disconnectFromServer();
    void sendToServer(const InputParser &input);
    void receiveFromServer(std::string &output);

    bool checkAccountConnection(std::string &output, QUERY_TYPE query);
public:
    Client() {this->connectToServer();};
    void mainLoop();
    bool connectionLoop();
};

#endif

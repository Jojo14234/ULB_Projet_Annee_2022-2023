#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "Controller/InputParser.hpp"


class Client {

	sf::TcpSocket socket;
	
	void connectToServer();
	void disconnectFromServer();

	void sendPacket(sf::Packet &packet);

public:

	Client() { this->connectToServer(); }

	// Send Queries
	void sendLogin(const std::string &username, const std::string &password);
	void sendRegister(const std::string &username, const std::string &password);
	void sendJoinGame(int code);
	bool sendCommand(InputParser &parser);

	void receive(std::string &output);

};

#endif

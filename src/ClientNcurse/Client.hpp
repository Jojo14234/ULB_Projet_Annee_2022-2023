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

	int game_code = 0;
	bool is_creator = false;

public:

	Client() { this->connectToServer(); }

	// Send Queries
	void sendLogin(const std::string &username, const std::string &password);
	void sendRegister(const std::string &username, const std::string &password);
	void sendJoinGame(int code);
	bool sendCommand(InputParser &parser);

	void receive(std::string &output);

	void setGameCode(int gc) { game_code = gc; }
	int getGameCode() { return game_code; }

	void createGame() { is_creator = true; }
	void leaveGame() { is_creator = false; } 
	bool isCreator() { return is_creator; }

};

#endif

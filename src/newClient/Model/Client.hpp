/**
 * Project Untitled
 */

#pragma once

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "Client.hpp"
#include "InputParser/MainInputParser.hpp"
#include "InputParser/GameInputParser.hpp"
#include "../../Server/ClientManager/QUERY.hpp"

class Client {

	sf::TcpSocket socket;
	
	void connectToServer();
	void disconnectFromServer();

	void sendPacket(sf::Packet &packet);

	int game_code = 0;
	bool is_creator = false;
	std::string user_name;

public:

	Client() { this->connectToServer(); }
    ~Client() { this->socket.disconnect(); }

	// Send Queries
	void sendLogin(const std::string &username, const std::string &password);
	void sendRegister(const std::string &username, const std::string &password);
	void sendJoinGame(int code);
	bool sendCommand(MainInputParser &parser);
	bool sendCommand(GameInputParser &parser);

	QUERY receive();
	QUERY receive(std::string &output);

	void setGameCode(int gc) { game_code = gc; }
	int getGameCode() { return game_code; }

	void createGame() { is_creator = true; }
	void leaveGame() { is_creator = false; } 
	bool isCreator() { return is_creator; }
	
	const std::string &getUsername() { return user_name; }

};
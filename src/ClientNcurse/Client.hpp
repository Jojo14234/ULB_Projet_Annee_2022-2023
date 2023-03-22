#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "InputParser/MainInputParser.hpp"
#include "InputParser/GameInputParser.hpp"
#include "../Server/ClientManager/QUERY.hpp"


class Client {

	sf::TcpSocket socket;
	
	void connectToServer();
	void disconnectFromServer();

	void sendPacket(sf::Packet &packet);

	int game_code = 0;
	bool is_creator = false;
	std::string user_name;
	bool is_my_turn = false;
	std::string player_turn;


public:

	Client() { this->connectToServer(); }

	// Send Queries
	void sendLogin(const std::string &username, const std::string &password);
	void sendRegister(const std::string &username, const std::string &password);
	void sendJoinGame(int code);
	bool sendCommand(MainInputParser &parser);
	bool sendCommand(GameInputParser &parser);

	void receive(std::string &output);
    void receiveQueryMsg(std::string &output, QUERY &query);

	void setGameCode(int gc) { game_code = gc; }
	int getGameCode() { return game_code; }

	void createGame() { is_creator = true; }
	void leaveGame() { is_creator = false; } 
	bool isCreator() { return is_creator; }
	bool isMyTurn() { return is_my_turn; }
	void startTurn() { is_my_turn = true; }
	void endTurn() { is_my_turn = false; }

	std::string getPlayerTurn() { return player_turn; }
	void setPlayerTurn(const std::string &player) { player_turn = player; }
	
	std::string getUsername() { return user_name; }
};

#endif

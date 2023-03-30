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
    // todo added from n-curse
    bool is_my_turn = false;
    std::string player_turn;

    //todo added from terminal
    bool connected_to_an_account = false;
    bool in_game = false;

public:

	Client() { this->connectToServer(); }
    ~Client() { this->socket.disconnect(); } // todo Maybe disconnect from server via disconnectFromServer

	// Send Queries
	void sendLogin(const std::string &username, const std::string &password);
	void sendRegister(const std::string &username, const std::string &password);
    void sendDisconnect();
	void sendJoinGame(int code);
	bool sendCommand(MainInputParser &parser); // todo == sendToServer in terminal
	bool sendCommand(GameInputParser &parser); // todo == sendToServer in terminal

	QUERY receive(std::string &output); // todo == receiveFromServer2 in terminal

	void setGameCode(int gc) { game_code = gc; }
	int getGameCode() const { return game_code; }

	void createGame() { is_creator = true; }
	void leaveGame() { is_creator = false; } 
	bool isCreator() const { return is_creator; }
    // todo added from n-curse
    bool isMyTurn() const { return is_my_turn; }
    void startTurn() { is_my_turn = true; }
    void endTurn() { is_my_turn = false; }
    std::string getPlayerTurn() const { return player_turn; }
    void setPlayerTurn(const std::string &player) { player_turn = player; }
	
	const std::string &getUsername() { return user_name; }

};
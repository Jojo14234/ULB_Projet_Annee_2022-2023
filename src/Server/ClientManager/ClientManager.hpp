#ifndef _SERVER_CLIENT_MANAGER_HPP
#define _SERVER_CLIENT_MANAGER_HPP

#include <SFML/Network.hpp>
#include <pthread.h>
#include <memory>
#include <string>

#include "../Game/GameServer.hpp"
#include "../../utils/Configs.hpp"
#include "../Database/User.hpp"


class ClientManager {

	sf::TcpSocket socket;

	// A link to the game server, nullptr if not in game
	GameServer* game_server;

	// If client is connected
	bool connected = true;

	// A link to his account
    User* account = nullptr;

	// The tid of the thread where the ClientManager is running
	pthread_t tid;

	struct args_t { int code; std::string s1; std::string s2; };
	args_t args;

public:

	// Send infos to the client
	void send(std::string &input);
    void send(std::string &&input) { this->send(input); }

	// Receive infos from the client
	void receive(QUERY_TYPE &query);
	void receive(GAME_QUERY_TYPE &query, sf::Packet &packet);

	// To compare
	bool operator==(const ClientManager& other) { return this->tid == other.tid; }

	// To enter the game
	void enterGameLoop() { this->game_server->clientLoop(*this); }

	// Disconnect the client
	void disconnect() { this->connected = false; }
	// If the client is connected
	bool isDisconnected() const { return not this->connected; }

	// If the client is in game
	bool inGame() const { return bool(game_server); }

	// GETTERS
	sf::TcpSocket &getSocket() { return this->socket; }
	pthread_t* getTidPtr() { return &(this->tid); }
    User* getAccount() { return this->account; }
	// To get args (parsed from the client)
	const struct args_t* getArgs() const { return &(this->args); }
	int getCode() const { return this->args.code; }
	const std::string& getS1() const { return this->args.s1; }
	const std::string& getS2() const { return this->args.s2; }

	// SETTERS
    void setAccount(User *user) { this->account = user; }
	void setGameServer(GameServer* gs) { this->game_server = gs; }
	void removeGameServer() { this->game_server = nullptr; }
};

#endif
#ifndef _CLIENT_MANAGER_HPP
#define _CLIENT_MANAGER_HPP

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
	std::shared_ptr<GameServer> game_server;

	// If client is connected
	bool connected = true;

    User* account = nullptr;

	// The tid of the thread where the ClientManager is running
	pthread_t tid;

	struct args_t { int code; std::string s1; std::string s2; };
	args_t args;

public:

	// Send infos to the client
	void send(std::string &input);
    void send(std::string &&input);

	// Receive infos from the client
	void receive(QUERY_TYPE &query);

	//
	bool operator==(const ClientManager& other) { return this->tid == other.tid; }

	// Disconnect the client
	void disconnect() { this->connected = false; }
	// If the client is connected
	bool isDisconnected() const { return not connected; }
	
	// If the client is in game
	bool inGame() const { return bool(game_server); }

	// To get args (parsed from the client)
	int getCode() const { return args.code; }
	const std::string& getS1() const { return args.s1; }
	const std::string& getS2() const { return args.s2; }

	// To set attributes
	sf::TcpSocket &getSocket() { return this->socket; }
	pthread_t* getTidPtr() { return &(this->tid); }


    void setAccount(User *user) {account = user;}
    User* getAccount() {return account;}

};


#endif

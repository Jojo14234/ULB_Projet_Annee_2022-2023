#ifndef _SERVER_HPP
#define _SERVER_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <pthread.h>

#include "ClientManager/ClientManagerList.hpp"
#include "Game/GameServerList.hpp"
#include "Database/Database.hpp"


class Server {
	
	sf::TcpListener listener;
	sf::TcpSocket socket;
	// List of all ClientManagers
	ClientManagerList clients;
	// List of all GameServers
	GameServerList games;
	bool server_online = true;
	Database database{"db.bin"};

	// Connect a new client
	void connectClient();

	// OWO
	void clientProcessQuery(ClientManager &client, QUERY_TYPE query);

    void clientProcessRegister(ClientManager &client);
    void clientProcessLogin(ClientManager &client);
    void clientProcessJoinGame(ClientManager &client);
    void clientProcessCreateGame(ClientManager &client);
    void clientProcessRanking(ClientManager &client);
    void clientProcessFriends(ClientManager &client);
    void clientProcessMessage(ClientManager &client);

public:

	Server();

	// Main Loop of the server
	void mainLoop();
	
	// Loop for the client
	void clientLoop(ClientManager &client);

};

#endif

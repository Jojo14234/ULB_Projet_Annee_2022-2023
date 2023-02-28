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
	
	// If the Server is online
	bool server_online = true;

	// The Database
	Database database{"db.bin"};

	// Connect a new client
	void connectClient();

	// To process the client query 
	void clientProcessQuery(ClientManager &client, QUERY_TYPE query);
	// For connection
	void clientProcessRegister(ClientManager &client);
	void clientProcessLogin(ClientManager &client);
	// For the game
	void clientProcessJoinGame(ClientManager &client);
	void clientProcessCreateGame(ClientManager &client);
	// For ranking
	void clientProcessRankingTop(ClientManager &client);
	void clientProcessRankingPos(ClientManager &client);
	// For friends
	void clientProcessFriendsList(ClientManager &client);
	void clientProcessFriendsRequest(ClientManager &client);
	void clientProcessFriendsAccept(ClientManager &client);
	void clientProcessFriendsRefuse(ClientManager &client);
	void clientProcessFriendsAdd(ClientManager &client);
	void clientProcessFriendsRemove(ClientManager &client);
	// For message
	void clientProcessShowMessage(ClientManager &client);
	void clientProcessSendMessage(ClientManager &client);

public:

	Server();

	// Main Loop of the server
	void mainLoop();
	
	// Loop for the client
	void clientLoop(ClientManager &client);

};

#endif
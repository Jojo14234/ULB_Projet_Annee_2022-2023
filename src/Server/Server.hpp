#ifndef _SERVER_HPP
#define _SERVER_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <pthread.h>

#include "ClientManager/ClientManagerList.hpp"
#include "Game/GameServer/GameServerList.hpp"
#include "Database/Database.hpp"
#include "../Utils/Config/Configs.hpp"


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
	Database database{DATA_PATH};

	// Connect a new client
	void connectClient();

    // For Disconnection of the user
    void clientProcessDisconnect(ClientManager &client, bool quit);
	// To process the client query
	void clientProcessQuery(ClientManager &client, QUERY_TYPE query);
	// For connection
	void clientProcessRegister(ClientManager &client);
	void clientProcessLogin(ClientManager &client);
	// For the game
	void clientProcessJoinGame(ClientManager &client);
	void clientProcessCreateGame(ClientManager &client);
    void clientProcessCreateFastGame(ClientManager &client);
	// For ranking
	void clientProcessRankingTop(ClientManager &client);
	void clientProcessRankingPos(ClientManager &client);
	void clientProcessRankingReset(ClientManager &client);
	// For friends
	void clientProcessFriendsInfo(ClientManager &client);
	void clientProcessFriendsList(ClientManager &client);
	void clientProcessFriendsRequest(ClientManager &client);
	void clientProcessFriendsAccept(ClientManager &client);
	void clientProcessFriendsRefuse(ClientManager &client);
	void clientProcessFriendsAdd(ClientManager &client);
	void clientProcessFriendsRemove(ClientManager &client);
	// For message
	void clientProcessShowMessage(ClientManager &client);
	void clientProcessSendMessage(ClientManager &client);

    // Find if the account is already connected
    bool find(User* user);

public:

	Server();

	// Main Loop of the server
	void mainLoop();
	
	// Loop for the client
	void clientLoop(ClientManager &client);

};

#endif
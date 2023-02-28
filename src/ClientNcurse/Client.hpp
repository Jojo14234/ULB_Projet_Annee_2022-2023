#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>


class Client {

///////////////////////////////////////////////////////////////////////
/////////////////           Client Variables         //////////////////
///////////////////////////////////////////////////////////////////////
	sf::TcpSocket socket;											 //
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/////////////////          Server Connection        ///////////////////
///////////////////////////////////////////////////////////////////////
	void connectToServer();											 //
	void disconnectFromServer();									 //
///////////////////////////////////////////////////////////////////////

	void sendPacket(sf::Packet &packet);

public:

///////////////////////////////////////////////////////////////////////
/////////////////        Client Constructor			///////////////////
///////////////////////////////////////////////////////////////////////
	Client() { this->connectToServer(); }							 //
///////////////////////////////////////////////////////////////////////
	
///////////////////////////////////////////////////////////////////////
/////////////////           Send Queries            ///////////////////
///////////////////////////////////////////////////////////////////////
	// Authentication
	void sendLogin(const std::string &username, const std::string &password);
	void sendRegister(const std::string &username, const std::string &password);
	// Game
	void sendJoinGame(int code);
	void sendCreateGame();
	// Ranking
	void sendRankTop();
	void sendRankPos();
	// Friends
	void sendFriendsList();
	void sendFriendsRequest();
	void sendFriendsAccept(const std::string &username);
	void sendFriendsDecline(const std::string &username);
	void sendFriendsAdd(const std::string &username);
	void sendFriendsRemove(const std::string &username);
	// Messages
	void sendMessageSend(const std::string &username, const std::string &message);
	void sendMessageRead(const std::string &username);
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/////////////////           Receive Queries         ///////////////////
///////////////////////////////////////////////////////////////////////
	void receive(std::string &output);								 //
///////////////////////////////////////////////////////////////////////


};

#endif

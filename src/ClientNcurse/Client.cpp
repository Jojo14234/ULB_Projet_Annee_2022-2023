#include <SFML/Network.hpp>

#include "Client.hpp"
#include "../utils/Configs.hpp"
#include "../utils/Exceptions.hpp"


// Private methods

void Client::connectToServer() {
	if (this->socket.connect(IP, PORT) != sf::Socket::Done) {
		throw ConnectServerClientException();	// can't connect to the server
	}
}

void Client::disconnectFromServer() {
	// TODO: send a disconnect query to the server
	this->socket.disconnect();
}

void Client::sendPacket(sf::Packet &packet) {
	if (this->socket.send(packet) != sf::Socket::Done) {
		throw WritePipeClientException(); // can't write on the socket
	}
}


// Public methods

// Send Query to the server

// Authentification
void Client::sendLogin(const std::string &username, const std::string &password) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::LOGIN);
	packet << username;
	packet << password;
	this->sendPacket(packet);
}

void Client::sendRegister(const std::string &username, const std::string &password) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::REGISTER);
	packet << username;
	packet << password;
	this->sendPacket(packet);
}

// Game

void Client::sendJoinGame(int code) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::JOIN_GAME);
	packet << code;
	this->sendPacket(packet);
}


bool Client::sendCommand(InputParser &parser) {
	QUERY_TYPE query = parser.getQueryType();
	if (query == QUERY_TYPE::NONE) return false;
	sf::Packet packet;
	packet << static_cast<int>(query);
	switch(query) {
	case QUERY_TYPE::FRIENDS_ACCEPT:
	case QUERY_TYPE::FRIENDS_REFUSE:
	case QUERY_TYPE::FRIENDS_ADD:
	case QUERY_TYPE::FRIENDS_REMOVE:
	case QUERY_TYPE::MESSAGE_SHOW: packet << parser[2]; break;
	case QUERY_TYPE::MESSAGE_SEND: packet << parser[1] << parser[2]; break;
	default: break;
	}
	this->sendPacket(packet);
	return true;
}


// Receive Query from the server

void Client::receive(std::string &output) {
	sf::Packet packet;
	if (this->socket.receive(packet) != sf::Socket::Done) {
		throw ReadPipeClientException(); // can't read on the socket
	}
	packet >> output;
}


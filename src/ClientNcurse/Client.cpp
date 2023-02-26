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

void Client::sendCreateGame() {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::CREATE_GAME);
	this->sendPacket(packet);
}

// Rank

void Client::sendRankTop() {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::RANKING_TOP);
	this->sendPacket(packet);
}

void Client::sendRankPos() {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::RANKING_POS);
	this->sendPacket(packet);
}

// Friends

void Client::sendFriendsList() {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::FRIENDS_LIST);
	this->sendPacket(packet);
}

void Client::sendFriendsRequest() {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::FRIENDS_REQUEST);
	this->sendPacket(packet);
}

void Client::sendFriendsAccept(const std::string &username) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::FRIENDS_ACCEPT);
	packet << username;
	this->sendPacket(packet);
}

void Client::sendFriendsDecline(const std::string &username) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::FRIENDS_REFUSE);
	packet << username;
	this->sendPacket(packet);
}

void Client::sendFriendsAdd(const std::string &username) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::FRIENDS_ADD);
	packet << username;
	this->sendPacket(packet);
}

void Client::sendFriendsRemove(const std::string &username) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::FRIENDS_REMOVE);
	packet << username;
	this->sendPacket(packet);
}

// Messages

void Client::sendMessageSend(const std::string &username, const std::string &message) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::MESSAGE_SEND);
	packet << username;
	packet << message;
	this->sendPacket(packet);
}

void Client::sendMessageRead(const std::string &username) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::MESSAGE_SHOW);
	packet << username;
	this->sendPacket(packet);
}


// Receive Query from the server

void Client::receive(std::string &output) {
	sf::Packet packet;
	if (this->socket.receive(packet) != sf::Socket::Done) {
		throw ReadPipeClientException(); // can't read on the socket
	}
	packet >> output;
}


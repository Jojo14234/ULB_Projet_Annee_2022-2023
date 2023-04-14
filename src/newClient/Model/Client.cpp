#include <SFML/Network.hpp>

#include "Client.hpp"
#include "../../utils/Configs.hpp"
#include "../../utils/Exceptions.hpp"


// Private methods

void Client::connectToServer() {
	if (this->socket.connect(IP, PORT) != sf::Socket::Done) {
		throw ConnectServerClientException();   // can't connect to the server
	}
}

void Client::disconnectFromServer() {
    sf::Packet packet;
    packet << static_cast<int>(QUERY_TYPE::DISCONNECT); //todo different from ncurse
    this->sendPacket(packet);
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
	this->user_name = username;
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::LOGIN);
	packet << username;
	packet << password;
	this->sendPacket(packet);
}

void Client::sendRegister(const std::string &username, const std::string &password) {
	this->user_name = username;
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::REGISTER);
	packet << username;
	packet << password;
	this->sendPacket(packet);
}

void Client::sendDisconnect() {
    sf::Packet packet;
    packet << static_cast<int>(QUERY_TYPE::QUIT);
    this->sendPacket(packet);
}

// Game

void Client::sendJoinGame(int code) {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::JOIN_GAME);
	packet << code;
	this->sendPacket(packet);
}


bool Client::sendCommand(MainInputParser &parser) {
	QUERY_TYPE query = parser.getQuery();
	if (query == QUERY_TYPE::NONE) { return false; }
	sf::Packet packet;
	packet << static_cast<int>(query);
	switch(query) {
	    case QUERY_TYPE::FRIENDS_ACCEPT:
	    case QUERY_TYPE::FRIENDS_REFUSE:
	    case QUERY_TYPE::FRIENDS_ADD:
	    case QUERY_TYPE::FRIENDS_REMOVE:
	    case QUERY_TYPE::MESSAGE_SHOW: packet << parser[2]; break;
	    case QUERY_TYPE::MESSAGE_SEND: packet << parser[1] << parser.regroup(2, parser.size(), ' '); break;
		case QUERY_TYPE::CREATE_FAST_GAME: 
		case QUERY_TYPE::CREATE_GAME: packet << parser.regroup(2, parser.size(), ' '); break;
	    default: break;
	}
	this->sendPacket(packet);
	return true;
}

bool Client::sendCommand(GameInputParser &parser) {
	GAME_QUERY_TYPE query = parser.getQuery();
	if (query == GAME_QUERY_TYPE::NONE) { return false; }
	sf::Packet packet;
	packet << static_cast<int>(query);
	switch(query) {
		// Add only the first argument to the packet //todo add other query
		case GAME_QUERY_TYPE::ARG1   :
		case GAME_QUERY_TYPE::BID    :
		case GAME_QUERY_TYPE::SELECT : packet << parser[1]; break;
		// Add both of the first and second arguments to the packet
		case GAME_QUERY_TYPE::TRADE :
		case GAME_QUERY_TYPE::ARG2   : packet << parser[1] << parser[2]; break;
		default : break;
	}
	this->sendPacket(packet);
	return true;
}

bool Client::sendCommand(GameInputParser &&parser) { return this->sendCommand(parser);}
bool Client::sendCommand(MainInputParser &&parser) { return this->sendCommand(parser);}

void Client::disconnectAccount() {
	sf::Packet packet;
	packet << static_cast<int>(QUERY_TYPE::DISCONNECT);
	sendPacket(packet);
}

// Receive Query from the server
QUERY Client::receive() {
	sf::Packet packet;
	if (this->socket.receive(packet) != sf::Socket::Done) {
		throw ReadPipeClientException(); // can't read on the socket
	}
	int tmp;
	packet >> tmp;
	return static_cast<QUERY>(tmp);
}

QUERY Client::receive(std::string &output) {
	sf::Packet packet;
	if (this->socket.receive(packet) != sf::Socket::Done) {
		throw ReadPipeClientException(); // can't read on the socket
	}
    int tmp;
	packet >> tmp >> output;
    return static_cast<QUERY>(tmp);
}

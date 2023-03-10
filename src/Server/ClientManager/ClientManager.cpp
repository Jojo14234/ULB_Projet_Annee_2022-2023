#include <SFML/Network.hpp>

#include "ClientManager.hpp"
#include "../Game/GameServer.hpp"
#include "../../utils/Exceptions.hpp"


void ClientManager::send(std::string &input) {
	sf::Packet packet;
	packet << input;
	if (this->socket.send(packet) !=  sf::Socket::Done) {
		throw WritePipeServerException();	// failed to write on the sokcet
	}
}

void ClientManager::send(std::string &&input) { this->send(input); }

void ClientManager::receive(QUERY_TYPE &query) {
	sf::Packet packet;
	if (this->socket.receive(packet) !=  sf::Socket::Done) { throw ReadPipeServerException(); }
	int tmp;
	packet >> tmp;
	query = static_cast<QUERY_TYPE>(tmp);
	switch (query) {
		case QUERY_TYPE::JOIN_GAME : packet >> args.code; break;
		
		case QUERY_TYPE::REGISTER :	// same as under
		case QUERY_TYPE::LOGIN :    // same as under
		case QUERY_TYPE::MESSAGE_SEND : packet >> args.s1 >> args.s2; break;
		
		case QUERY_TYPE::MESSAGE_SHOW :  // same as under
		case QUERY_TYPE::FRIENDS_ACCEPT: // same as under
		case QUERY_TYPE::FRIENDS_REFUSE: // same as under
		case QUERY_TYPE::FRIENDS_ADD:    // same as under
		case QUERY_TYPE::FRIENDS_REMOVE: packet >> args.s1; break;
		default : break;
	}
}

void ClientManager::receive(GAME_QUERY_TYPE &query, sf::Packet &packet) {
	if (this->socket.receive(packet) !=  sf::Socket::Done) { throw ReadPipeServerException(); }
	int tmp;
	packet >> tmp;
	query = static_cast<GAME_QUERY_TYPE>(tmp);
}

void ClientManager::receive(GAME_QUERY_TYPE &query) {
    sf::Packet packet;
    if (this->socket.receive(packet) !=  sf::Socket::Done) { throw ReadPipeServerException(); }
    int tmp;
    packet >> tmp;
    query = static_cast<GAME_QUERY_TYPE>(tmp); //TODO je comprends pas le fonctionnement...
}

bool ClientManager::operator==(const ClientManager& other) { return this->tid == other.tid; }

void ClientManager::enterGameLoop() { this->game_server->addPlayer(*this); this->game_server->clientLoop(*this); }

void ClientManager::disconnect() { this->connected = false; }
// If the client is connected
bool ClientManager::isDisconnected() const { return not this->connected; }

bool ClientManager::inGame() const { return bool(game_server); }

sf::TcpSocket &ClientManager::getSocket() { return this->socket; }
pthread_t* ClientManager::getTidPtr() { return &(this->tid); }
User* ClientManager::getAccount() { return this->account; }

//const struct args_t *ClientManager::getArgs() const { return &(this->args); }

int ClientManager::getCode() const { return this->args.code; }
const std::string& ClientManager::getS1() const { return this->args.s1; }
const std::string& ClientManager::getS2() const { return this->args.s2; }

void ClientManager::setAccount(User *user) { this->account = user; }
void ClientManager::setGameServer(GameServer* gs) { this->game_server = gs; }
void ClientManager::removeGameServer() { this->game_server = nullptr; }

GameServer* ClientManager::getGameServer(){
    return game_server;
}
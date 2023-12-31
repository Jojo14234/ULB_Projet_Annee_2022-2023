#include <SFML/Network.hpp>
#include <vector>
#include <string>

#include "ClientManager.hpp"
#include "../Game/GameServer/GameServer.hpp"
#include "../../Utils/Exceptions.hpp"


// SEND INFOS TO THE CLIENT
void ClientManager::send(const std::string &input) {
	sf::Packet packet;
	packet << (int)QUERY::MESSAGE << input;
	if ( this->socket.send(packet) !=  sf::Socket::Done ) { throw WritePipeServerException(); } // failed to write on the socket
}

void ClientManager::sendQueryMsg(const std::string &input, QUERY query) {
    sf::Packet packet;
    packet << (int)query << input;
    if ( this->socket.send(packet) !=  sf::Socket::Done ) { throw WritePipeServerException(); } // failed to write on the socket
}

void ClientManager::sendFriendsInfo(const std::vector<std::string> &friends, const std::vector<std::string> &requests) {
	sf::Packet packet;
	packet << (int)friends.size() << (int)requests.size();
	for ( const auto &arg : friends ) { packet << arg; }
	for ( const auto &arg : requests ) { packet << arg; }
	if ( this->socket.send(packet) !=  sf::Socket::Done ) { throw WritePipeServerException(); } // failed to write on the socket
}

// RECEIVE INFOS FROM THE CLIENT
void ClientManager::receive(QUERY_TYPE &query) {
	sf::Packet packet;
	if ( this->socket.receive(packet) != sf::Socket::Done ) { throw ReadPipeServerException(); }
	int tmp;
	packet >> tmp;
	query = static_cast<QUERY_TYPE>(tmp);
	switch ( query ) {
		case QUERY_TYPE::JOIN_GAME : packet >> args.code; break;
		
		case QUERY_TYPE::REGISTER :	// same as under
		case QUERY_TYPE::LOGIN :    // same as under
        case QUERY_TYPE::CREATE_GAME :
        case QUERY_TYPE::CREATE_FAST_GAME :
		case QUERY_TYPE::MESSAGE_SEND : packet >> args.s1 >> args.s2; break;
		case QUERY_TYPE::RANKING_POS:
		case QUERY_TYPE::RANKING_TOP: break;
		case QUERY_TYPE::MESSAGE_SHOW :  // same as under
		case QUERY_TYPE::FRIENDS_ACCEPT: // same as under
		case QUERY_TYPE::FRIENDS_REFUSE: // same as under
		case QUERY_TYPE::FRIENDS_ADD:    // same as under
		case QUERY_TYPE::FRIENDS_REMOVE: packet >> args.s1; break;
		default : break;
	}
}

void ClientManager::receive(GAME_QUERY_TYPE &query, sf::Packet &packet) {
	if ( this->socket.receive(packet) !=  sf::Socket::Done ) { throw ReadPipeServerException(); }
	int tmp;
	packet >> tmp;
	query = static_cast<GAME_QUERY_TYPE>(tmp);
}

void ClientManager::receive(GAME_QUERY_TYPE &query) {
    sf::Packet packet;
    if ( this->socket.receive(packet) !=  sf::Socket::Done ) { throw ReadPipeServerException(); }
    int tmp;
    packet >> tmp;
    query = static_cast<GAME_QUERY_TYPE>(tmp);
}

// COMPARE
bool ClientManager::operator==(const ClientManager& other) { return this->tid == other.tid; }


void ClientManager::enterGameLoop() {
    GameStats stats = this->game_server->clientLoop(*this);
    this->getAccount()->updateStats(stats);
    this->removeGameServer();
}

void ClientManager::disconnect() { this->connected = false; }

// If the client is connected (same functions but names are useful for some functions comprehensions)
bool ClientManager::isDisconnected() const { return not this->connected; }
bool ClientManager::isConnected() const { return this->connected; }

// If the client is in game
bool ClientManager::inGame() const { return bool(game_server); }

// GETTER
sf::TcpSocket &ClientManager::getSocket()   { return this->socket; }
pthread_t* ClientManager::getTidPtr()       { return &(this->tid); }
User* ClientManager::getAccount()           const { return this->account; }
std::string ClientManager::getUsername()    const { return this->username; }
GameServer* ClientManager::getGameServer()  const { return game_server; }
int ClientManager::getCode()                const { return this->args.code; }
const std::string& ClientManager::getS1()   const { return this->args.s1; }
const std::string& ClientManager::getS2()   const { return this->args.s2; }

// Gestion account
void ClientManager::setAccount(User *user) {
    this->account = user;
    this->username = user->getUsername();
}
void ClientManager::removeAccount() {
    this->account = nullptr;
}

// Gestion gameServer
void ClientManager::setGameServer(GameServer* gs) { this->game_server = gs; }
void ClientManager::removeGameServer() { this->game_server = nullptr; }

// Gestion stats
void ClientManager::setScore(int new_score) { this->score = new_score; }
void ClientManager::setIsWinner(bool winner) { this->isWinner = winner; }

int ClientManager::getScore() const { return this->score; }
bool ClientManager::getIsWinner() const { return this->isWinner; }

void ClientManager::resetStat() {
    this->score = 0;
    this->isWinner = false;
}


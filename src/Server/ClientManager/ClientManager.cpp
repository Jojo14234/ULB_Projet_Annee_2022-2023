#include <SFML/Network.hpp>

#include "ClientManager.hpp"
#include "../../utils/Exceptions.hpp"


void ClientManager::send(std::string &input) {
	sf::Packet packet;
	packet << input;
	if (this->socket.send(packet) !=  sf::Socket::Done) { throw WritePipeServerException(); }
}

void ClientManager::send(std::string &&input) {
    std::string n_input = input;
    send(n_input);
}

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
		case QUERY_TYPE::MESSAGE : packet >> args.s1 >> args.s2; break;
		
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

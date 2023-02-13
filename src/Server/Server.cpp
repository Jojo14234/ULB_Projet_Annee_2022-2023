#include <memory>
#include <pthread.h>

#include "Server.hpp"
#include "ClientManager/ClientManager.hpp"
#include "SigHandler.hpp"
#include "../utils/Exceptions.hpp"
#include "../utils/Configs.hpp"


// Public

Server::Server() {
	// Bind the socket to a port
	if (listener.listen(PORT) != sf::Socket::Done) {
		throw CreateServerException();
	}
	SigHandler::setup();
}

void Server::mainLoop() {
	while (this->server_online) {
		this->clients.clean();
		try { this->connectClient(); }
		catch (const ConnectClientServerException &exception) {
			if (SigHandler::askedLeaving()) { this->server_online = false; }
		}
	}
}

void Server::clientLoop(ClientManager &client) {
    database.print_in_file();
	// Loop to exchange data with the client
	while (true) {
		
		// Receive a query
		QUERY_TYPE query; 
		client.receive(query);
		std::cout << "Receive: " << (int)query << " from client: " << client.getSocket().getRemoteAddress() << std::endl;
		
		// Execute the query
		this->clientProcessQuery(client, query);
        if (query == QUERY_TYPE::DISCONNECT && client.getAccount() == nullptr) {break;}
        if (query == QUERY_TYPE::DISCONNECT && client.getAccount()) {
            std::cout << client.getAccount()->getUsername() <<" just disconnected from his account" << std::endl;
            client.setAccount(nullptr);
        }
	}
    //TODO : Gérer la déconnexion proprement du client
}


// Thread
struct thread_args_t { ClientManager* client; Server* server; };

void* clientThread(void* args) {
	Server *server = ((thread_args_t*)args)->server;
	ClientManager *client = ((thread_args_t*)args)->client;
	// Start the loop for the client
	server->clientLoop(*client);
	delete (thread_args_t*)args;
	return NULL;
}


// Private

void Server::connectClient() {
	// Create a client
	std::shared_ptr<ClientManager> client = std::make_shared<ClientManager>();
	// Wait a connection
	if (listener.accept(client->getSocket()) != sf::Socket::Done) { throw ConnectClientServerException(); }
	this->clients.add(client);
	// Send the new client into a thread
	thread_args_t *thread_args = new thread_args_t{client.get(), this};
	SigHandler::mask();
	pthread_create(client->getTidPtr(), NULL, &clientThread, thread_args);
	SigHandler::unmask();
}

void Server::clientProcessQuery(ClientManager &client, QUERY_TYPE query) {
	switch (query) {
		case QUERY_TYPE::LOGIN :
			this->clientProcessLogin(client);
			break;
		case QUERY_TYPE::REGISTER :
			this->clientProcessRegister(client);
			break;
		case QUERY_TYPE::JOIN_GAME :
			this->clientProcessJoinGame(client);
			break;
		case QUERY_TYPE::CREATE_GAME :
			this->clientProcessCreateGame(client);
			break;	
		case QUERY_TYPE::RANKING : 
			this->clientProcessRanking(client);
			break;
		case QUERY_TYPE::FRIENDS : 
			this->clientProcessFriends(client);
			break;
		case QUERY_TYPE::MESSAGE : 
			this->clientProcessMessage(client);
			break;
        case QUERY_TYPE::DISCONNECT :
            client.send("Déconnexion");
            break;
		default : break;
	}
}

void Server::clientProcessRegister(ClientManager &client) {
    if (client.getAccount() != nullptr) {
        client.send("You are already connected");
        return;}
    std::cout << "New register request : " << client.getS1() << " " <<client.getS2() << std::endl;

    if (!this->database.contains(client.getS1().c_str())) {
        database.addUser(client.getS1(), client.getS2());
        database.save();
        std::cout << "Register approved" << std::endl;

        //TODO := verif =: connecter le client à son compte fraichement créer
        client.setAccount(this->database.getUser(client.getS1().c_str()));

        //renvoyer au client comme quoi la création a réussi
        client.send("TRUE");
    }
    else {
        std::cout << "Register not approved, this Username is already taken" << std::endl;
        //renvoyer au client comme quoi la création a échoué
        client.send("FALSE");
    }
}

void Server::clientProcessLogin(ClientManager &client) {
    if (client.getAccount() != nullptr) {
        client.send("You are already connected");
        return;}
    std::cout << "New login request : " << client.getS1() << " " << client.getS2() << std::endl;

    if (this->database.contains(client.getS1().c_str()) &&
        this->database.getUser(client.getS1().c_str())->isPassword(client.getS2().c_str())) {
        std::cout << "Login approved" << std::endl;
        //TODO := verif =: Log le client avec son compte
        client.setAccount(this->database.getUser(client.getS1().c_str()));

        //renvoyer au client comme quoi la connexion a réussi
        client.send("TRUE");
    }
    else {
        std::cout << "Login not approved" << std::endl;
        //renvoyer au client comme quoi la connexion a échoué
        client.send("FALSE");
    }
}

void Server::clientProcessJoinGame(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

void Server::clientProcessCreateGame(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

void Server::clientProcessRanking(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

void Server::clientProcessFriends(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

void Server::clientProcessMessage(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}


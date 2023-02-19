#include <memory>
#include <pthread.h>
#include <string>

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
		if (query == QUERY_TYPE::DISCONNECT) {
			if (!client.getAccount()) { break; }
			std::cout << client.getAccount()->getUsername() << " disconnected from his account !" << std::endl;
			client.setAccount(nullptr);
		}
	}
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
		// For connection
		case QUERY_TYPE::LOGIN: this->clientProcessLogin(client); break;
		case QUERY_TYPE::REGISTER: this->clientProcessRegister(client); break;
		// For game
		case QUERY_TYPE::JOIN_GAME: this->clientProcessJoinGame(client); break;
		case QUERY_TYPE::CREATE_GAME: this->clientProcessCreateGame(client); break;
		// For ranking
		case QUERY_TYPE::RANKING_POS: this->clientProcessRankingPos(client); break;
		case QUERY_TYPE::RANKING_TOP: this->clientProcessRankingTop(client); break;
		// For friends
		case QUERY_TYPE::FRIENDS_SHOW: this->clientProcessFriendsShow(client); break;
		case QUERY_TYPE::FRIENDS_REQUEST: this->clientProcessFriendsRequest(client); break;
		case QUERY_TYPE::FRIENDS_ACCEPT: this->clientProcessFriendsAccept(client); break;
		case QUERY_TYPE::FRIENDS_REFUSE: this->clientProcessFriendsRefuse(client); break;
		case QUERY_TYPE::FRIENDS_ADD: this->clientProcessFriendsAdd(client); break;
		case QUERY_TYPE::FRIENDS_REMOVE: this->clientProcessFriendsRemove(client); break;
		// For message
		case QUERY_TYPE::MESSAGE: this->clientProcessMessage(client); break;
		// For disconnect
		case QUERY_TYPE::DISCONNECT: client.send("DISCONNECT"); break;
		default : break;
	}
}


// For connection
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

// For game
void Server::clientProcessJoinGame(ClientManager &client) {
	std::string output = "aucune partie n'existe avec ce code";
	if (games.joinGame(&client, client.getCode())) { 
		output = "GAME";
		client.send(output);
		client.enterGameLoop();
	} else { client.send(output); }
}

void Server::clientProcessCreateGame(ClientManager &client) {
	std::string output = "vous avez crée une partie avec le code : ";
	int code = games.createGame(&client);
	output += std::to_string(code);
	client.send(output);
	client.enterGameLoop();
}

// For ranking
void Server::clientProcessRankingPos(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

void Server::clientProcessRankingTop(ClientManager &client) {
	std::vector<User*> ranking;
	database.getRanking(ranking);
	std::string input = "";
	for (int i(1); i <= 5; i++) {
		//std::cout << i << ". " << ranking[i]->getUsername() << " avec " << ranking[i]->getStats().getScore() << " points." << std::endl;
		input += std::to_string(i) + ". " + ranking[i]->getUsername() + " avec " + std::to_string(ranking[i]->getStats().getScore()) + " point(s).\n";
	}
	client.send(input);
}

// For friends
void Server::clientProcessFriendsShow(ClientManager &client) {
	client.send(client.getAccount()->getFriendList().toString(this->database));
}

void Server::clientProcessFriendsRequest(ClientManager &client) {
	client.send(client.getAccount()->getFriendRequestList().toString(this->database));
}

void Server::clientProcessFriendsAccept(ClientManager &client) {
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
	if (new_friend == nullptr) { 
		client.send("Le pseudo entré n'existe pas."); return;
	}
	if (client_account->isFriendWith(*new_friend)) { 
		client.send("Vous êtes déjà ami avec ce joueur !"); return; 
	}
	if ( ! client_account->hasReceiveFriendRequestFrom(*new_friend)) {
		client.send("Ce joueur ne vous a pas demandé en ami!"); return;
	}
	client.getAccount()->acceptRequest(new_friend->getId(), database);
	std::string s = "Vous êtes désormais ami avec ";
	s += new_friend->getUsername();
	s += "!";
	client.send(s);
}

void Server::clientProcessFriendsRefuse(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

void Server::clientProcessFriendsAdd(ClientManager &client) {
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
	if (new_friend == nullptr) { 
		client.send("Le pseudo entré n'existe pas."); return; 
	}
	if (client_account == new_friend){
		client.send("Vous ne pouvez pas être ami avec vous même."); return;
	}
	if (client_account->isFriendWith(*new_friend)) { 
		client.send("Vous êtes déjà ami avec ce joueur !"); return; 
	}
	if (client_account->hasSentFriendRequestTo(*new_friend)) { 
		client.send("Vous avez déjà envoyé une demande d'ami à ce joueur !"); return; 
	}
	if (client_account->hasReceiveFriendRequestFrom(*new_friend)) {
		std::string s = "Cet utilisateur vous a déjà demandé en ami.\nVous êtes donc désormais ami avec ";
		s += new_friend->getUsername();
		s += "!";
		client.send(s);
		client.getAccount()->acceptRequest(new_friend->getId(), database); return;
	}

	client.getAccount()->sendRequest(new_friend->getId(), database);
	client.send("La demande d'ami a bien été envoyée !"); 
}

void Server::clientProcessFriendsRemove(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

// For message
void Server::clientProcessMessage(ClientManager &client) {
	client.inGame();	// pour pas avoir le warning unused parameter et empecher la compilation
}

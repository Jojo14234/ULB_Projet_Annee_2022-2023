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
		throw CreateServerException();	// the server can't be created
	}
	SigHandler::setup();
}

void Server::mainLoop() {
	while (this->server_online) {
		this->clients.clean();	// join ended threads and remove disconnected clients
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
		// Receive a query from the client
		QUERY_TYPE query; 
		client.receive(query);
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
	if (listener.accept(client->getSocket()) != sf::Socket::Done) {
		throw ConnectClientServerException();	// can't connect a new client
	}
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
		case QUERY_TYPE::FRIENDS_LIST: this->clientProcessFriendsList(client); break;
		case QUERY_TYPE::FRIENDS_REQUEST: this->clientProcessFriendsRequest(client); break;
		case QUERY_TYPE::FRIENDS_ACCEPT: this->clientProcessFriendsAccept(client); break;
		case QUERY_TYPE::FRIENDS_REFUSE: this->clientProcessFriendsRefuse(client); break;
		case QUERY_TYPE::FRIENDS_ADD: this->clientProcessFriendsAdd(client); break;
		case QUERY_TYPE::FRIENDS_REMOVE: this->clientProcessFriendsRemove(client); break;
		// For message
		case QUERY_TYPE::MESSAGE_SHOW: this->clientProcessShowMessage(client); break;
		case QUERY_TYPE::MESSAGE_SEND: this->clientProcessSendMessage(client); break;
		// For disconnect
		case QUERY_TYPE::DISCONNECT: client.send("DISCONNECT"); break;
		default : std::cout << "Unknown query type" << std::endl; break;
	}
}


// For connection
void Server::clientProcessRegister(ClientManager &client) {
	std::cout << "Received 'register' query from client: " << client.getSocket().getRemoteAddress() << std::endl;
	if (client.getAccount() != nullptr) {
		client.send("You are already connected");
	} else if (!this->database.contains(client.getS1().c_str())) {
		User* user = database.addUser(client.getS1(), client.getS2());
		database.save();
		std::cout << "Register succeed with username : " << client.getS1() << std::endl;
		client.setAccount(user);
		client.send("TRUE");	// succeed
	} else {
		std::cout << "Register failed with username : " << client.getS1() << std::endl;
		client.send("FALSE");	// failed
	}
}

void Server::clientProcessLogin(ClientManager &client) {
	std::cout << "Received 'login' query from client: " << client.getSocket().getRemoteAddress() << std::endl;
	if (client.getAccount() != nullptr) {
		client.send("You are already connected");
		return;}
	User* user = database.getUser(client.getS1().c_str());
	if (user == nullptr) {
		std::cout << "Login failed, the username : " << client.getS1() << " doesn't exist" << std::endl;
		client.send("FALSE");	// failed
	} else if (!user->isPassword(client.getS2().c_str())) {
		std::cout << "Login failed, the password entered is incorrect" << std::endl;
		client.send("FALSE");	// failed
	}
	else {
		client.setAccount(user);
		std::cout << "Login succeed with username : " << client.getS1() << std::endl;
		client.send("TRUE");	// succeed
	}
}

// For game
void Server::clientProcessJoinGame(ClientManager &client) {
	std::cout << "Received 'join' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	std::string output = "aucune partie n'existe avec ce code";
	if (games.joinGame(&client, client.getCode())) { 
		output = "GAME";
		client.send(output);
		client.enterGameLoop();
	} else {
		std::cout << "Join failed, the code correspond to any game" << std::endl;
		client.send(output);
	}
}

void Server::clientProcessCreateGame(ClientManager &client) {
	std::cout << "Received 'create' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	std::string output = "vous avez crée une partie avec le code : ";
	int code = games.createGame(&client);
	output += std::to_string(code);
	client.send(output);
	client.enterGameLoop();
}

// For ranking
void Server::clientProcessRankingPos(ClientManager &client) {
	std::cout << "Received 'ranking pos' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	client.send("don't need a position, you're too good!");
}

void Server::clientProcessRankingTop(ClientManager &client) {
	std::cout << "Received 'ranking top' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername()  << std::endl;
	std::vector<User*> ranking;
	database.getRanking(ranking);
	std::string input = "";
	for (int i(1); i <= 5; i++) {
		input += std::to_string(i) + ". " + ranking[i]->getUsername() + " avec " + std::to_string(ranking[i]->getStats().getScore()) + " point(s).\n";
	}
	client.send(input);
}

// For friends
void Server::clientProcessFriendsList(ClientManager &client) {
	std::cout << "Received 'friend list' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername()  << std::endl;
	client.send(client.getAccount()->getFriendList().toString(this->database));
}

void Server::clientProcessFriendsRequest(ClientManager &client) {
	std::cout << "Received 'friend request' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername()  << std::endl;
	client.send(client.getAccount()->getFriendRequestList().toString(this->database));
}

void Server::clientProcessFriendsAccept(ClientManager &client) {
	std::cout << "Received 'friend accept' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
	if (new_friend == nullptr) {
		std::cout << "Accept failed, the user doesn't exist" << std::endl;
		client.send("Le pseudo entré n'existe pas.");
	} else if (client_account->isFriendWith(*new_friend)) {
		std::cout << "Accept failed, already friends" << std::endl;
		client.send("Vous êtes déjà ami avec ce joueur !"); 
	} else if ( ! client_account->hasReceiveFriendRequestFrom(*new_friend)) {
		std::cout << "Accept failed, the friend request doesn't exist" << std::endl;
		client.send("Ce joueur ne vous a pas demandé en ami!");
	} else {
		std::cout << "Accept succeed, " << client.getAccount()->getUsername() << " and " << new_friend->getUsername() << " are now friends" << std::endl;
		client_account->acceptRequest(new_friend->getId(), database);
		std::string s = "Vous êtes désormais ami avec ";
		s += new_friend->getUsername();
		s += "!";
		client.send(s);
	}
}

void Server::clientProcessFriendsRefuse(ClientManager &client) {
	std::cout << "Received 'friend refuse' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	std::cout << new_friend->getUsername() << std::endl;
	User* client_account = client.getAccount();
	std::cout << client_account->getUsername() << std::endl;
	if (new_friend == nullptr) {
		std::cout << "Refuse failed, the user doesn't exist" << std::endl;
		client.send("Le pseudo entré n'existe pas.");
	} else if ( ! client_account->hasReceiveFriendRequestFrom(*new_friend)) {
		std::cout << "Accept failed, the friend request doesn't exist" << std::endl;
		client.send("Ce joueur ne vous a pas demandé en ami!");
	} else {
		std::cout << "Refuse succeed, " << client.getAccount()->getUsername() << " and " << new_friend->getUsername() << " will not be friends" << std::endl;
		client_account->removeRequest(new_friend->getId(), database);
		std::string s = "Vous avez refusé la demande d'ami de ";
		s += new_friend->getUsername();
		s += ".";
		client.send(s);
	}
}

void Server::clientProcessFriendsAdd(ClientManager &client) {
	std::cout << "Received 'friend add' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
	if (new_friend == nullptr) { 
		std::cout << "Add failed, the user doesn't exist" << std::endl;
		client.send("Le pseudo entré n'existe pas.");
	} else if (client_account == new_friend){
		std::cout << "Add failed, can't be friend with himself" << std::endl;
		client.send("Vous ne pouvez pas être ami avec vous même.");
	} else if (client_account->isFriendWith(*new_friend)) {
		std::cout << "Add failed, already friends" << std::endl;
		client.send("Vous êtes déjà ami avec ce joueur !");
	} else if (client_account->hasSentFriendRequestTo(*new_friend)) { 
		std::cout << "Add failed, friend request already sent" << std::endl;
		client.send("Vous avez déjà envoyé une demande d'ami à ce joueur !");
	} else if (client_account->hasReceiveFriendRequestFrom(*new_friend)) {
		std::cout << "Add succeed but this user already sent him a request so " << client.getAccount()->getUsername() << " and " << new_friend->getUsername() << " are now friends" << std::endl;
		std::string s = "Cet utilisateur vous a déjà demandé en ami.\nVous êtes donc désormais ami avec ";
		s += new_friend->getUsername();
		s += "!";
		client.send(s);
		client_account->acceptRequest(new_friend->getId(), database); return;
	} else {
		std::cout << "Add succeed, " << client.getAccount()->getUsername() << " sent a request to " << new_friend->getUsername() << std::endl;
		client_account->sendRequest(new_friend->getId(), database);
		client.send("La demande d'ami a bien été envoyée !"); 
	}
}

void Server::clientProcessFriendsRemove(ClientManager &client) {
	std::cout << "Received 'friend remove' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
	if (new_friend == nullptr) {
		std::cout << "Remove failed, the user doesn't exist" << std::endl;
		client.send("Le pseudo entré n'existe pas.");
	} else if ( ! client_account->isFriendWith(*new_friend)) {
		std::cout << "Remove failed, not friend with" << std::endl;
		client.send("Vous n'êtes pas ami avec ce joueur !");
	} else {
		std::cout << "Remove succeed, " << client.getAccount()->getUsername() << " and " << new_friend->getUsername() << " are no longer friends" << std::endl;
		client_account->removeFriend(new_friend->getId(), database);
		std::string s = "Vous n'êtes désormais plus ami avec ";
		s += new_friend->getUsername();
		s += ".";
		client.send(s);
	}
}

// For message

void Server::clientProcessShowMessage(ClientManager &client) {
	std::cout << "Received 'message show' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	User* user = database.getUser(client.getS1().c_str());
	Conversation* conv = database.getConv(client.getAccount(), user);
	if (user == nullptr) {
		std::cout << "Message show failed, the user doesn't exist" << std::endl;
		client.send("Le pseudo entré n'existe pas.");
	} else if (conv == nullptr) {
		std::cout << "Message show failed, the conversation doesn't exist" << std::endl;
		client.send("Aucune conversation avec ce joueur na été trouvée !");
	} else {
		std::cout << "Message show succeed" << std::endl;
		std::string output = std::string{*conv};
		client.send(output);
	}
}

void Server::clientProcessSendMessage(ClientManager &client) {
	std::cout << "Received 'message send' query from client: " << client.getSocket().getRemoteAddress() << " > " << client.getAccount()->getUsername() << std::endl;
	User* user = database.getUser(client.getS1().c_str());
	if (user == nullptr) {
		std::cout << "Message show failed, the user doesn't exist" << std::endl;
		client.send("Le pseudo entré n'existe pas.");
	} else if (!client.getAccount()->isFriendWith(user->getId())) {
		std::cout << "Message show failed, not friends" << std::endl;
		client.send("Vous n'êtes pas ami avec ce joueur !");
	} else {
		std::cout << "Message show succeed" << std::endl;
		database.sendMsg(client.getAccount(), user, client.getS2());
		std::string s = "Vous avez bien envoyé un message à ";
		s += user->getUsername();
		s += ".";
		client.send(s);
	}
}

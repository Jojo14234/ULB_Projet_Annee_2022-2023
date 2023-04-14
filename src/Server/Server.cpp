#include <memory>
#include <pthread.h>
#include <string>
#include <vector>

#include "Server.hpp"
#include "ClientManager/ClientManager.hpp"
#include "ClientManager/QUERY.hpp"
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
			if (SigHandler::askedLeaving()) {
                this->server_online = false;
                for (auto client : this->clients) {
                    client->disconnect();
                }
            }
		}
	}
}

void Server::clientLoop(ClientManager &client) {
	database.print_in_file();
	try {
        QUERY_TYPE query;
		while (true) {
			client.receive(query);
            this->clientProcessQuery(client, query);
            if (query == QUERY_TYPE::QUIT && !client.getAccount()) { break; }

        }
        std::cout << "[one client went out of the Server::clientLoop(), he disconnect the normal way]" << std::endl;
        client.disconnect();
    }
	catch (const WritePipeServerException &exception) { std::cout << "[Exception catch (Server::clientLoop)] > " << exception.what() << std::endl; }
	catch (const ReadPipeServerException &exception)  { std::cout << "[Exception catch (Server::clientLoop)] > " << exception.what() << std::endl; }
	client.disconnect();
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
		case QUERY_TYPE::LOGIN:             this->clientProcessLogin(client); break;
		case QUERY_TYPE::REGISTER:          this->clientProcessRegister(client); break;
		// For game
		case QUERY_TYPE::JOIN_GAME:         this->clientProcessJoinGame(client); break;
		case QUERY_TYPE::CREATE_GAME:       this->clientProcessCreateGame(client); break;
		case QUERY_TYPE::CREATE_FAST_GAME:  this->clientProcessCreateGame(client); break;
		// For ranking
		case QUERY_TYPE::RANKING_POS:       this->clientProcessRankingPos(client); break;
		case QUERY_TYPE::RANKING_TOP:       this->clientProcessRankingTop(client); break;
        case QUERY_TYPE::RANKING_RESET:     this->clientProcessRankingReset(client); break;
		// For friends
        case QUERY_TYPE::FRIENDS_INFO:      this->clientProcessFriendsInfo(client); break;
		case QUERY_TYPE::FRIENDS_LIST:      this->clientProcessFriendsList(client); break;
		case QUERY_TYPE::FRIENDS_REQUEST:   this->clientProcessFriendsRequest(client); break;
		case QUERY_TYPE::FRIENDS_ACCEPT:    this->clientProcessFriendsAccept(client); break;
		case QUERY_TYPE::FRIENDS_REFUSE:    this->clientProcessFriendsRefuse(client); break;
		case QUERY_TYPE::FRIENDS_ADD:       this->clientProcessFriendsAdd(client); break;
		case QUERY_TYPE::FRIENDS_REMOVE:    this->clientProcessFriendsRemove(client); break;
		// For message
		case QUERY_TYPE::MESSAGE_SHOW:      this->clientProcessShowMessage(client); break;
		case QUERY_TYPE::MESSAGE_SEND:      this->clientProcessSendMessage(client); break;
		// For disconnect
        case QUERY_TYPE::DISCONNECT:        this->clientProcessDisconnect(client); break;
        case QUERY_TYPE::QUIT:              this->clientProcessQuit(client); break;
		default : std::cout << "[(Server::clientProcessQuery()) Unknown query type]" << std::endl; break;
	}
}

// Deconnection
void Server::clientProcessDisconnect(ClientManager &client) {
    std::cout << "[Received 'disconnect' query from client]" << std::endl;
    std::cout << "[Client using " + client.getUsername() + " disconnected from his account]" << std::endl;
    client.sendQueryMsg("DISCONNECT", QUERY::DISCONNECT);
    client.setAccount(nullptr);
}

void Server::clientProcessQuit(ClientManager &client) {
    std::cout << "[Received 'quit' query from client]" << std::endl;
    client.sendQueryMsg("DISCONNECT", QUERY::DISCONNECT);
    client.removeAccount();
}



// For connection
void Server::clientProcessRegister(ClientManager &client) {
	std::cout << "[Received 'register' query from client]" << std::endl;
    // Condition du process
    if ( client.getAccount() != nullptr ) { client.send("You are already connected"); return; }
    if ( this->database.contains(client.getS1().c_str()) ) { client.sendQueryMsg("FALSE", QUERY::FALSEQ); return; }
    // Process of creating the new account
    User* user = database.addUser(client.getS1(), client.getS2());
    database.save();
    client.setAccount(user);
    client.sendQueryMsg("TRUE", QUERY::TRUEQ);	// succeed
    std::cout << "[Register client account '"<< client.getAccount()->getUsername() <<"' was successful]\n" << std::endl;
}

void Server::clientProcessLogin(ClientManager &client) {
	std::cout << "[Received 'login' query from client]" << std::endl;
    // Condition du process
    if (client.getAccount() != nullptr)              { client.sendQueryMsg("You are already connected", QUERY::TRUEQ); return; }
	User* user = database.getUser(client.getS1().c_str());
	if ( user == nullptr )                           { client.sendQueryMsg("FALSE", QUERY::FALSEQ); return; }	// User not find in the db
    if ( !user->isPassword(client.getS2().c_str()) ) { client.sendQueryMsg("FALSE", QUERY::FALSEQ); return; }  // Incorrect password
    if ( this->find(user) )                          { client.sendQueryMsg("FALSE", QUERY::TRUEQ); return; }  // Si le compte utilisateur est déjà
    // Process of linking account                                                                             // utilisé par un autre client
    client.setAccount(user);
    client.sendQueryMsg("TRUE", QUERY::TRUEQ);	// succeed
    std::cout << "['login' to client account '"<< client.getAccount()->getUsername() <<"' was successful]\n" << std::endl;

}

bool Server::find(User* user) {
    for (auto client : this->clients) {
        if (client->getAccount() == user) { return true; }
    }
    return false;
}

// For game
void Server::clientProcessJoinGame(ClientManager &client) {
	std::cout << "[Received 'join' query from client  '" << client.getAccount()->getUsername() << "']\n" << std::endl;
    if ( !games.joinGame(&client, client.getCode()) ) { client.sendQueryMsg("", QUERY::FALSEQ); return; }
    //client.sendQueryMsg(client.getUsername() + ":" + std::to_string(client.getCode()), QUERY::PLAYER_JOIN_GAME);
    client.enterGameLoop();
}

void Server::clientProcessCreateGame(ClientManager &client) {
	std::cout << "[Received 'create normal' query from client '" << client.getAccount()->getUsername() << "']\n" << std::endl;
    std::istringstream input{client.getS1()};
    int space = 0;
    GameParameters params{false};
    for (std::string word; std::getline(input, word, ' '); space++) {
        std::cout << "Param " << space << " : " << word << std::endl;
        switch (space) {
            case 0: {
                try{
                    params.startMoney = std::stoi(word);
                } catch ( ... ){
                    params.startMoney = 1500;
                }
                break;
            }
            case 1: { 
                try{
                    params.maxPlayers = std::stoi(word);
                    if (params.maxPlayers > 6) params.maxPlayers = 6;
                } catch ( ... ){
                    params.maxPlayers = 6;
                }
                break;
            }
            case 2: { 
                try{
                    params.maxHome = std::stoi(word);
                } catch ( ... ){
                    params.maxHome = 32;
                }
                break;
            }
            case 3: { 
                try {
                    params.maxHotel = std::stoi(word);
                } catch ( ... ){
                    params.maxHotel = 12;
                }
                break;
            }
            default : break;
        }
    }
    int gc = games.createGame(&client, params);
    std::string res = client.getUsername() + ":" + std::to_string(gc) + ":" + std::to_string(params.isFastGame) + ":" +
                      std::to_string(params.startMoney) + ":" + std::to_string(params.maxPlayers) + ":" +
                      std::to_string(params.maxHome) + ":" + std::to_string(params.maxHotel) + ":" + std::to_string(params.max_turn);
    client.sendQueryMsg(res, QUERY::PLAYER_CREATE_GAME);
	client.enterGameLoop();
}

void Server::clientProcessCreateFastGame(ClientManager &client) {
    std::cout << "[Received 'create fast' query from client '" << client.getAccount()->getUsername() << "']\n" << std::endl;
    std::istringstream input{client.getS2()};
    int space = 0;
    GameParameters params{true};
    for (std::string word; std::getline(input, word, ' '); space++) {
        std::cout << word << std::endl;
        switch (space) {
            case 0: params.startMoney = std::stoi(word); break;
            case 1: params.maxPlayers = std::stoi(word); break;
            case 2: params.maxHome = std::stoi(word); break;
            case 3: params.maxHotel = std::stoi(word); break;
            default : break;
        }
    }
    int gc = games.createGame(&client, params);
    client.send("(clientProcessCreateGame) Vous avez crée une partie rapide avec le code : " + std::to_string(gc));
    client.enterGameLoop();
}

// For ranking
void Server::clientProcessRankingPos(ClientManager &client) {
	std::cout << "[Received 'ranking pos' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	std::string pos = std::to_string(database.getRankingPos(client.getAccount()));
    std::string score = std::to_string(client.getAccount()->getStats().getScore());
	client.send("Votre position dans le classement est " + pos + " avec un score de " + score);
    std::cout << "['ranking pos' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;

}

void Server::clientProcessRankingTop(ClientManager &client) {
	std::cout << "[Received 'ranking top' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	std::array<const User*, 5> top = this->database.getRanking();
	std::string input = "";
	for (int i=0; i < 5 && top[i] != nullptr ; i++) {
        std::string pos = std::to_string(i+1);
        std::string user = top[i]->getUsername();
        std::string points = std::to_string(top[i]->getStats().getScore());
		input += pos + ". " + user + " avec " + points + " point(s).\n";
	}
	client.send(input);
    std::cout << "['ranking top' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;

}

void Server::clientProcessRankingReset(ClientManager &client) {
    if (client.getUsername() == "admin") { this->database.resetRanking(); }
    client.send("reset");
}

// For friends
void Server::clientProcessFriendsInfo(ClientManager &client) {
    std::cout << "[Received 'friend info' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
    const std::vector<std::string> friends = client.getAccount()->getFriendList().toVector(this->database);
    const std::vector<std::string> requests = client.getAccount()->getFriendRequestList().toVector(this->database);
    client.sendFriendsInfo(friends, requests);
    std::cout << "['friend info' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;
}

void Server::clientProcessFriendsList(ClientManager &client) {
	std::cout << "[Received 'friend list' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	client.send(client.getAccount()->getFriendList().toString(this->database));
    std::cout << "['friend list' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;
}

void Server::clientProcessFriendsRequest(ClientManager &client) {
	std::cout << "[Received 'friend request' query from client '" << client.getAccount()->getUsername() << "']\n" << std::endl;
	client.send(client.getAccount()->getFriendRequestList().toString(this->database));
}

void Server::clientProcessFriendsAccept(ClientManager &client) {
	std::cout << "\n[Received 'friend accept' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
    // Condition du process
	if ( new_friend == nullptr )                     { client.send("Le pseudo entré n'existe pas."); return; }
    if ( client_account->isFriendWith(*new_friend) ) { client.send("Vous êtes déjà ami avec ce joueur !"); return; }
    if ( !client_account->hasReceiveFriendRequestFrom(*new_friend) ) { client.send("Ce joueur ne vous a pas demandé en ami!"); return; }
    // Process of accepting a friend request
    client_account->acceptRequest(new_friend->getId(), database);
    client.send(std::string("Vous êtes désormais ami avec " + new_friend->getUsername() + " !"));
    std::cout << "['friend accept' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;
}

void Server::clientProcessFriendsRefuse(ClientManager &client) {
	std::cout << "[Received 'friend refuse' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
    // Condition du process
	if (new_friend == nullptr)                                       { client.send("Le pseudo entré n'existe pas."); return; }
    if ( !client_account->hasReceiveFriendRequestFrom(*new_friend) ) { client.send("Ce joueur ne vous a pas demandé en ami!"); return; }
    // Process of refusing friend request
    client_account->removeRequest(new_friend->getId(), database);
    client.send("Vous avez refusé la demande d'ami de " + new_friend->getUsername() + ".");
    std::cout << "['friend refuse' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;
}

void Server::clientProcessFriendsAdd(ClientManager &client) {
	std::cout << "[Received 'friend add' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
    // Condition du process
    if (new_friend == nullptr)                                  { client.send("Le pseudo entré n'existe pas."); return; }
    if ( client_account == new_friend )                         { client.send("Vous ne pouvez pas être ami avec vous même."); return; }
    if ( client_account->isFriendWith(*new_friend) )            { client.send("Vous êtes déjà ami avec ce joueur !"); return; }
    if ( client_account->hasSentFriendRequestTo(*new_friend) )  { client.send("Vous avez déjà envoyé une demande d'ami à ce joueur !"); return; }
    // Process of making them friends
    if ( client_account->hasReceiveFriendRequestFrom(*new_friend) ) {
        client_account->acceptRequest(new_friend->getId(), database);
        client.send("Cet utilisateur vous a déjà demandé en ami.\nVous êtes donc désormais ami avec " + new_friend->getUsername() + " !");
        std::cout << "['friend add' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;
        return;
	}
    // Process of sending request
    client_account->sendRequest(new_friend->getId(), database);
    client.send("La demande d'ami a bien été envoyée !");
    std::cout << "['friend add' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;

}

void Server::clientProcessFriendsRemove(ClientManager &client) {
	std::cout << "\n[Received 'friend remove' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* client_account = client.getAccount();
    // Condition of process
	if ( new_friend == nullptr )                      { client.send("Le pseudo entré n'existe pas."); return; }
    if ( !client_account->isFriendWith(*new_friend) ) { client.send("Vous n'êtes pas ami avec ce joueur !"); return; }
    // Process of removing one friend
    client_account->removeFriend(new_friend->getId(), database);
    client.send("Vous n'êtes désormais plus ami avec " + new_friend->getUsername() + ".");
    std::cout << "['friend remove' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;

}

// For message

void Server::clientProcessShowMessage(ClientManager &client) {
	std::cout << "[Received 'message show' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	User* user = database.getUser(client.getS1().c_str());
	Conversation* conv = database.getConv(client.getAccount(), user);
    // Condition of the process
    if ( user == nullptr ) { client.send("Le pseudo entré n'existe pas."); return; }
    if ( conv == nullptr ) { client.send("Aucune conversation avec ce joueur na été trouvée !"); return; }
    // Process of showing a message
    client.send(std::string{*conv});
    std::cout << "['message show' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;

}

void Server::clientProcessSendMessage(ClientManager &client) {
	std::cout << "[Received 'message send' query from client '" << client.getAccount()->getUsername() << "']" << std::endl;
	User* user = database.getUser(client.getS1().c_str());
    // Condition of the process
	if (user == nullptr)                                     { client.send("Le pseudo entré n'existe pas."); return; }
    if ( !client.getAccount()->isFriendWith(user->getId()) ) { client.send("Vous n'êtes pas ami avec ce joueur !"); return; }
    // Process of sending a message
    database.sendMsg(client.getAccount(), user, client.getS2());
    client.send("Vous avez bien envoyé un message à " + user->getUsername() + ".");
    std::cout << "['message send' query from client '" << client.getAccount()->getUsername() << "' was successful]\n" << std::endl;
}

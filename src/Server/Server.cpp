#include <memory>
#include <pthread.h>
#include <string>
#include <vector>

#include "Server.hpp"
#include "ClientManager/ClientManager.hpp"
#include "ClientManager/QUERY.hpp"
#include "Handler/SigHandler.hpp"
#include "../Utils/Exceptions.hpp"
#include "../Utils/Config/Configs.hpp"
#include "../Utils/Sentences/Sentences.hpp"



// Public

Server::Server() {
	// Bind the socket to a port, if return false : the server can't be created
	if (listener.listen(PORT) != sf::Socket::Done) { throw CreateServerException(); }
	SigHandler::setup();
}

void Server::mainLoop() {
	while (this->server_online) {
        // join ended threads and remove disconnected clients
		this->clients.clean();

		try { this->connectClient(); }
		catch (const ConnectClientServerException &exception) {
			if (SigHandler::askedLeaving()) {
                this->server_online = false;
                for (auto client : this->clients) { client->disconnect(); }
            }
		}
	}
}

void Server::clientLoop(ClientManager &client) {
	try {
        QUERY_TYPE query;
		while (true) {
			client.receive(query);
            this->clientProcessQuery(client, query);
            if (query == QUERY_TYPE::QUIT && !client.getAccount()) { break; }
        }
        ServerSentence::DisconnectNormal();
        client.disconnect();
    }
	catch (const WritePipeServerException &exception) {ServerSentence::WriteException(exception.what());}
	catch (const ReadPipeServerException &exception)  {ServerSentence::ReadException(exception.what());}
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
		case QUERY_TYPE::CREATE_FAST_GAME:  this->clientProcessCreateFastGame(client); break;
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
        case QUERY_TYPE::DISCONNECT:        this->clientProcessDisconnect(client, false); break;
        case QUERY_TYPE::QUIT:              this->clientProcessDisconnect(client, true); break;
        default : ServerSentence::UnknownQueryType(); break;
	}
}

// Disconnection / Quitting
void Server::clientProcessDisconnect(ClientManager &client, bool quit) {
    ServerSentence::DisconnectAccount(client.getUsername(), quit);
    client.sendQueryMsg("DISCONNECT", QUERY::DISCONNECT);
    client.removeAccount();
}

// Register an account
void Server::clientProcessRegister(ClientManager &client) {
    bool success = true;

    // Process conditions
    // 1. Not be connected,
    // 2. Database must not already contain this account.
    if ( client.getAccount() != nullptr )                       { success = false; }
    else if ( this->database.contains(client.getS1().c_str()) ) { success = false; }

    // Process of creating the new account
    if (success) { client.setAccount(database.addUser(client.getS1(), client.getS2())); }

    // Send result to client
    client.sendQueryMsg("", static_cast<QUERY>(success));
    ServerSentence::RegisterAccount(client.getUsername(), success);
}

// Login to an account
void Server::clientProcessLogin(ClientManager &client) {
    bool success = true;
    User* user = database.getUser(client.getS1().c_str());

    // Process conditions
    // 1. Account mus exist in the db
    // 2. Password must be correct
    // 3. Account cannot be already bind with another client
    if ( !user )                                          { success = false; }
    else if ( !user->isPassword(client.getS2().c_str()) ) { success = false; }
    else if ( this->find(user) )                          { success = false; }

    // Process of binding account and client
    if (success) {client.setAccount(user);}

    // Send result to client
    client.sendQueryMsg("", static_cast<QUERY>(success));
    ServerSentence::LoginAccount(client.getS1().c_str(), success);
}

// Joining Game
void Server::clientProcessJoinGame(ClientManager &client) {
    bool success = true;

    // Process condition
    // 1. gameCode must exist.
    if ( !games.joinGame(&client, client.getCode()) ) { success = false; }

    // Send result to client
    client.sendQueryMsg("", static_cast<QUERY>(success));
    ServerSentence::JoinGame(client.getUsername(), client.getCode(), success);

    // Entering the game
    if (success) { client.enterGameLoop(); }
}

// Creating Game
void Server::clientProcessCreateGame(ClientManager &client) {
    // Parsing of parameters
    GameParameters params{false, client.getS1()};

    // Game creation
    int gc = games.createGame(&client, params);

    // Send result to client
    client.sendQueryMsg(params.to_string(client.getUsername(), gc), QUERY::PLAYER_CREATE_GAME);
    ServerSentence::CreateGame(client.getUsername(), params, true);

    // Entering the game
	client.enterGameLoop();
}

// Creating fastGame
void Server::clientProcessCreateFastGame(ClientManager &client) {
    // Parsing of parameters
    GameParameters params{true, client.getS1()};

    // Game creation
    int gc = games.createGame(&client, params);

    // Send result to client
    client.sendQueryMsg(params.to_string(client.getUsername(), gc), QUERY::PLAYER_CREATE_GAME);
    ServerSentence::CreateGame(client.getUsername(), params, true);

    // Entering the game
    client.enterGameLoop();
}


// For ranking
void Server::clientProcessRankingPos(ClientManager &client) {
	client.sendQueryMsg(this->database.getRankingPosString(client.getAccount()), QUERY::RANKING_POS);
    ServerSentence::RankingPos(client.getUsername(), true);

}

void Server::clientProcessRankingTop(ClientManager &client) {
	client.sendQueryMsg(this->database.getRankingTopString(), QUERY::RANKING_TOP);
    ServerSentence::RankingTop(client.getUsername(), true);
}

void Server::clientProcessRankingReset(ClientManager &client) {
    if (client.getUsername() == "admin") { this->database.resetRanking(); }
    client.send(""); // todo vérifier si on est obligé de renvoyer qqch ou pas.
    ServerSentence::ResetRank(client.getUsername());
}

// For friends
void Server::clientProcessFriendsInfo(ClientManager &client) {
    const std::vector<std::string> friends = client.getAccount()->getFriendList().toVector(this->database);
    const std::vector<std::string> requests = client.getAccount()->getFriendRequestList().toVector(this->database);
    client.sendFriendsInfo(friends, requests);
    ServerSentence::FriendInfo(client.getUsername());
}

void Server::clientProcessFriendsList(ClientManager &client) {
	client.send(client.getAccount()->getFriendList().toString(this->database));
    ServerSentence::FriendList(client.getUsername());
}

void Server::clientProcessFriendsRequest(ClientManager &client) {
	client.send(client.getAccount()->getFriendRequestList().toString(this->database));
    ServerSentence::FriendRequest(client.getUsername());
}

void Server::clientProcessFriendsAccept(ClientManager &client) {
    bool success = true;
	User* new_friend = database.getUser(client.getS1().c_str());
	User* me = client.getAccount();

    // Process conditions
    // 1. New friends must exist in the db
    // 2. They are not already friends
    // 3. He sent you a friend request
	if ( new_friend == nullptr )                              { success = false; }
    else if ( me->isFriendWith(*new_friend) )                 { success = false; }
    else if ( !me->hasReceiveFriendRequestFrom(*new_friend) ) { success = false; }

    // accepting a friend request
    if (success) { me->acceptRequest(new_friend->getId(), database); }

    // Send result to client
    client.send("");
    ServerSentence::FriendAccept(client.getUsername(), client.getS1(), success);
}

void Server::clientProcessFriendsRefuse(ClientManager &client) {
    bool success = true;
	User* remove_friend = database.getUser(client.getS1().c_str());
	User* me = client.getAccount();

    // Process conditions
    // 1. remove_friend must exist in the db.
    // 2. remove_friend should have sent you a friend request
	if (remove_friend == nullptr)                                { success = false; }
    else if ( !me->hasReceiveFriendRequestFrom(*remove_friend) ) { success = false; }

    // Refusing friend request
    if (success) { me->removeRequest(remove_friend->getId(), database); }

    // Send result to client
    client.send("");
    ServerSentence::FriendRefuse(client.getUsername(), client.getS1().c_str(), success);
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

// Search in the connected account if the user is connected
bool Server::find(User* user) {
    for (auto client : this->clients) {
        if (client->getAccount() == user) { return true; }
    }
    return false;
}
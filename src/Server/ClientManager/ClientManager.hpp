#ifndef _SERVER_CLIENT_MANAGER_HPP
#define _SERVER_CLIENT_MANAGER_HPP

#include <SFML/Network.hpp>
#include <pthread.h>
#include <memory>
#include <string>
#include <vector>

#include "../../utils/Configs.hpp"
#include "../Database/User.hpp"
#include "QUERY.hpp"


class GameServer;	// forward declaration

class ClientManager {

	sf::TcpSocket socket;

	// A link to the game server, nullptr if not in game
	GameServer* game_server;

    // Classement dans la partie
    int score = 0;
    bool isWinner = false;

	// If client is connected
	bool connected = true;

	// A link to his account
    User* account = nullptr;

	// The tid of the thread where the ClientManager is running
	pthread_t tid;

	struct args_t { int code; std::string s1; std::string s2; };
	args_t args;

public:
    ClientManager()=default;

	// Send infos to the client
	void send(const std::string &input);
  void sendQueryMsg(const std::string &input, QUERY query);
	void sendFriendsInfo(const std::vector<std::string> &friends, const std::vector<std::string> &requests); 
  void send(QUERY &query, const std::string &input);

	// Receive infos from the client
	void receive(QUERY_TYPE &query);
	void receive(GAME_QUERY_TYPE &query, sf::Packet &packet);
  void receive(GAME_QUERY_TYPE &query);

	// To compare
	bool operator==(const ClientManager& other);

	// To enter the game
	void enterGameLoop();

	// Disconnect the client
	void disconnect();
	// If the client is connected (same functions but names are useful for some functions comprehensions)
	bool isDisconnected() const;
	bool isConnected() const;

	// If the client is in game
	bool inGame() const;

	// GETTERS
	sf::TcpSocket &getSocket();
	pthread_t* getTidPtr();
    User* getAccount() const;
	// To get args (parsed from the client)
	const struct args_t* getArgs() const { return &(this->args); }
    std::string getUsername() const;
    GameServer* getGameServer() const;
	int getCode() const;
	const std::string& getS1() const ;
	const std::string& getS2() const;
    int getScore() const;
    bool getIsWinner() const;



    // SETTERS
    void setAccount(User *user);
    void removeAccount();
	void setGameServer(GameServer* gs);
	void removeGameServer();
    void setScore(int score);
    void setIsWinner(bool winner);
    void resetStat();

};

#endif
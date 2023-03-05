#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>

#include "../utils/Configs.hpp"

#include "Player.hpp"
#include "Board/Board.hpp"
#include "../Game/Board/Obtainable/Cells/LandCell.hpp"


class ClientManager;


class Capitalist {
    std::vector<Player> players;
    int current_player_index = 0;
    bool running = false;

    Board board;
    Dice dice;

public:

	Capitalist()=default;

	void receiveQuery(GAME_QUERY_TYPE query, sf::Packet &packet);

	//void sendMessage(std::string &output) { output = "coucou ici capitalist"; }

    void addPlayer(ClientManager &client);
    void removePlayer(){;
    void startGame();

    /*
    Player* getPlayerByClientId(int id){
        for (auto &player : players){
            if (player.getId() == id){
                return &player;
            }
        } return nullptr;
    }
*/
    Player* getCurrentPlayer();

    bool isRunning();

    void endCurrentTurn();

    int rollDice();

    bool rolledADouble();

    Player* getPlayerByClient(ClientManager &client);
    Dice* getDice();
    Board* getBoard();

    int getNumberOfPlayers();

    std::vector<Player>* getPlayers();
    void startAuction();

    Player* identifyAuctionWinner();

    LandCell* getCellByName(std::string& name);
};

#endif
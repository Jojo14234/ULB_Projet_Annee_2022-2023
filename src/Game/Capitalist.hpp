#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>

#include "../utils/Configs.hpp"

#include "Player.hpp"
#include "Board/Board.hpp"
#include "../Game/Board/Obtainable/Cells/LandCell.hpp"


class ClientManager;


class CapitalistUI {
public:
    CapitalistUI()=default;

    std::string refactorName(std::string name) {
        unsigned int size_diff = name.size() - 8;
        for (unsigned int i = 0; i < size_diff; i++) {
            name += " ";
        }
        return name;
    }

    std::string refactorValue(int value) {
        if (value < 10) {return " " + std::to_string(value);}
        return std::to_string(value);
    }

    std::string RollDiceMessage(std::string name, int value, bool isDouble) {
        std::string str = "";
        str += "+———————————————————————————————CAPITALI$T———————————————————————————————+\n";
        str += ("|        Le joueur [" + this->refactorName(name) + "] a jeté les dés.            |\n");
        str += ("|              Valeur des dés [" + this->refactorValue(value) + "]                      |\n");
        if (isDouble) {
            str += ("|         Vous avez obtenus un double [" + std::to_string(value/2) + "]             |\n");
            str += ("|                      Iel va pouvoir rejouer !|                         |\n");
        }
        str += "+————————————————————————————————————————————————————————————————————————+";
        return str;
    }
};

class Capitalist {
    std::vector<Player> players;
    int current_player_index = 0;
    bool running = false;

    int auction_in_progress = 0;

    Board board;
    Dice dice;
    CapitalistUI ui{};

public:

	Capitalist()=default;

	void receiveQuery(GAME_QUERY_TYPE query, sf::Packet &packet);

	//void sendMessage(std::string &output) { output = "coucou ici capitalist"; }

    void addPlayer(ClientManager &client);
    void removePlayer();
    void startGame();
    CapitalistUI getUI() {return ui;}

    /*
    Player* getPlayerByClientId(int id){
        for (auto &player : players){
            if (player.getId() == id)
                return &player;
            }
        } return nullptr;
    }
*/

    Player* getCurrentPlayer();

    bool isRunning();

    void endCurrentTurn();

    int rollDice();
    std::string getRollString();

    bool rolledADouble();

    Player* getPlayerByClient(ClientManager &client);
    Dice* getDice();
    Board* getBoard();

    int getNumberOfPlayers();

    std::vector<Player>* getPlayers();
    void startAuction();
    void stopAuction();

    Player* identifyAuctionWinner();

    LandCell* getCellByName(std::string& name);

    int auctionInProgress() { return auction_in_progress;}
    void setAuctionProgress(int progress) {auction_in_progress = progress;}
};


#endif
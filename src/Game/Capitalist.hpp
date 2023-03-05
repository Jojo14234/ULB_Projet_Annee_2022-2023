#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>


#include "../utils/Configs.hpp"
#include "../Server/ClientManager/ClientManager.hpp"
#include "Player.hpp"
#include "Board/Board.hpp"
#include "../Game/Board/Obtainable/Cells/LandCell.hpp"


class Capitalist {
    std::vector<Player> players;
    int current_player_index = 0;
    bool running = false;

    Board board;
    Dice dice;

public:

	Capitalist()=default;

	void receiveQuery(GAME_QUERY_TYPE query, sf::Packet &packet) {
		std::string s1="", s2="";
		switch (query) {
			case GAME_QUERY_TYPE::ARG1 : packet >> s1; break;
			case GAME_QUERY_TYPE::ARG2 : packet >> s1 >> s2; break;
            case GAME_QUERY_TYPE::LEAVE : removePlayer(); break;
			default : break;
		}
		std::cout << "in capitalist : " << (int)query << " " << s1 << " " << s2 << std::endl;
	}

    void displayGameStatus(){
        std::cout << players.size() << "are present in this game." << std::endl;
        std::cout << "Player 1 is on tile number " << players.at(0).getIndexOnBoard() << std::endl;
    };

	void sendMessage(std::string &output) { output = "coucou ici capitalist"; }

    void addPlayer(ClientManager &client){
        players.push_back(Player(&client));
        if (players.size() == 1) {players[0].setAdmin(); players[0].setCurrentlyPlaying(true);}
    }
    void removePlayer(){
        //TODO : find correspinding id of player to delete
        players.pop_back();
    }
    void startGame(){ running = true; }

    /*
    Player* getPlayerByClientId(int id){
        for (auto &player : players){
            if (player.getId() == id){
                return &player;
            }
        } return nullptr;
    }
*/
    Player* getCurrentPlayer(){ return &players[current_player_index]; }

    bool isRunning() {return running;}

    void endCurrentTurn(){
        players[current_player_index].setCurrentlyPlaying(false);
        (current_player_index += 1) %= (players.size());
        players[current_player_index].setCurrentlyPlaying(true);
        players[current_player_index].getClient()->send("C'est à votre tour.");
    }

    int rollDice(){
        return dice.roll();
    }

    bool rolledADouble(){
        return dice.isDouble();
    }

    Player* getPlayerByClient(ClientManager &client){
        Player* ret = nullptr;
        for (auto &player : players){
            if (player.getClient() == &client){
                ret = &player;
                break;
            }
        }
        return ret;
    }
    Dice* getDice(){
        return &dice;
    }
    Board* getBoard(){
        return &board;
    }

    int getNumberOfPlayers() {
        return players.size();
    }

    std::vector<Player>* getPlayers(){
        return &players; //ça marche ceci?
    }
    void startAuction(){
        for (auto &player : players){
            if (player.getPlayerStatus() != PLAYER_STATUS::BANKRUPT){
                player.auctionStart();
            }
            else {
                player.leaveAuction();
            }
        }
    }

    Player* identifyAuctionWinner(){
        Player* winner = nullptr;
        for (auto player : players){
            if (player.isInAuction()){
                if (winner == nullptr){
                    winner = &player;
                }
                else {
                    return nullptr;
                }
            }
        }
        return winner;
    }

    LandCell* getCellByName(std::string& name){
        return board.getCellByName(name);
    }
};

#endif
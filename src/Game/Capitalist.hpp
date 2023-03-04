#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>


#include "../utils/Configs.hpp"
#include "Player.hpp"
#include "Board/Board.hpp"


class Capitalist {
    std::vector<Player> players;
    int current_player_index = 0;
    bool running = false;

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

    void addPlayer(int &id){
        players.push_back(Player(id));
        if (players.size() == 1) {players[0].setAdmin(); players[0].setCurrentlyPlaying(true);}
    }
    void removePlayer(){
        //TODO : find correspinding id of player to delete
        players.pop_back();
    }
    void startGame(){ running = true; }

    Player* getPlayerByClientId(int id){
        for (auto &player : players){
            if (player.getId() == id)
                return &player;
        }
    }
    
    Player* getCurrentPlayer(){ return &players[current_player_index]; }

    bool isRunning() {return running;}

    void endCurrentTurn(){
        players[current_player_index].setCurrentlyPlaying(false);
        (current_player_index += 1) %= (players.size());
        players[current_player_index].setCurrentlyPlaying(true);
    }

    int rollDice(){
        return dice.roll();
    }

    bool rolledADouble(){
        return dice.isDouble();
    }
};

#endif
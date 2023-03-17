#ifndef _GAME_START_PARSER2_HPP
#define _GAME_START_PARSER2_HPP

#include <string>
#include <vector>
#include <array>

struct PlayersInformations {
	int player_nb;
	std::vector<std::string> player_usernames;
};

class GameStartParser {

	std::string state_str;
	PlayersInformations res;

public:

	GameStartParser(std::string player_info_str) : state_str{player_info_str} {};

	void parse(){
        bool player_insert = false;
        unsigned int i = 0;
        int player = 0;
        std::string tmp;

        while(i < state_str.size()){
            if (i == 0){
                res.player_nb = state_str[i];
                res.player_usernames.resize(state_str[i]);
            }
            else if (state_str[i] == '|'){
                if (player_insert == true){
                    res.player_usernames[player] = tmp;
                    player++;
                    player_insert = false;

                }
                else{player_insert = true;}
            }}}
            
    const PlayersInformations& getBufferSplit() const { return res;}        
            
            
            
};




#endif

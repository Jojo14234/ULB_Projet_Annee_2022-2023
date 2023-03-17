#ifndef _GAME_START_PARSER_HPP
#define _GAME_START_PARSER_HPP

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
		bool first_semicolon = true;
		int player_index = 0;
		std::string tmp;

		for (char c : state_str){
			if (c == '-' or c == 'P'){
				tmp.clear();
			}
			else if (c == ';'){
				if (first_semicolon) { 
					res.player_nb = atoi(tmp.c_str()); 
					res.player_usernames.resize(res.player_nb);
				 	first_semicolon = false;
				}
				else { res.player_usernames[player_index] = tmp; }
				tmp.clear();
			}
			else if (c == ':'){
				player_index = atoi(tmp.c_str());
				tmp.clear();
			}
			else {
				tmp += c;
			}
		}
	}


	const PlayersInformations& getBufferSplit() const { return res; }
};



#endif
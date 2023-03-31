#ifndef _GAME_LAUNCHING_PARSER_HPP
#define _GAME_LAUNCHING_PARSER_HPP

#include <string>
#include <vector>
#include <array>

struct PlayersInformations {
	int beginner;
	int player_nb;
	std::vector<std::string> player_usernames;
};

struct JoinInfo {
	std::string username;
	int game_code;
	int nb_player;
	std::vector<std::string> player_usernames;
};


class GameLaunchingParser {

	std::string str;
	PlayersInformations res;
	JoinInfo join;

public:

	GameLaunchingParser(std::string player_info_str) : str{player_info_str} {};

	const PlayersInformations& parseStartInfo(){
		int rod_nb = 0;
		int player = 0;
		std::string tmp;

		for (char c : str){
			if (c == '|'){
				if (rod_nb == 0){
					res.player_nb = atoi(tmp.c_str());
					res.player_usernames.resize(res.player_nb);
				}
				else if (rod_nb == 1){
					res.beginner = atoi(tmp.c_str());
				}
				else {
					res.player_usernames[player] = tmp;
				}
				rod_nb++;
				tmp.clear();
			}
			else if (c == '='){
				player = atoi(tmp.c_str());
				tmp.clear();
			}
			else tmp += c;
		}

		return res;
	}

	const JoinInfo& parseCreateInfo() {
		std::string tmp;
		int i = 0;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		join.username = tmp;
		join.game_code = atoi(&str[i+1]);
		join.nb_player = 1;
		join.player_usernames.push_back(tmp);
		return join;
	}

	const JoinInfo& parseJoinInfo() {
		std::string tmp = "";
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { join.username = tmp; break;}
					case 1: { join.game_code = atoi(tmp.c_str()); break;}
					case 2: { join.nb_player = atoi(tmp.c_str()); break;}
					default: { join.player_usernames.push_back(tmp); }
				}
				colon_nb++;	
				tmp.clear();
			} else tmp += c;
		}
		join.player_usernames.push_back(tmp);
		return join;
	}
};


#endif
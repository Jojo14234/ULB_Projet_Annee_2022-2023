#ifndef _GAME_LAUNCHING_PARSER_HPP
#define _GAME_LAUNCHING_PARSER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>

struct StartInfo {
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

public:

	GameLaunchingParser(std::string str) : str{str} {};


	// returns a struct of a string of the form
	// username:gameCode [string]:[int]
	std::shared_ptr<JoinInfo> parseCreateQuery() {
		std::shared_ptr<JoinInfo> res = std::make_shared<JoinInfo>();
		std::string tmp;
		int i = 0;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->username = tmp;
		res->game_code = atoi(&str[i+1]);
		res->nb_player = 1; //the game just has been created, there is only one person.
		res->player_usernames.push_back(tmp); //he is the only person in the game
		return res;
	}


	// returns a struct of a string of the form
	// username:gameCode:nb_player:{usernames} [string]:[int]:[int]:{[string]}
	std::shared_ptr<JoinInfo> parseJoinQuery() {
		std::shared_ptr<JoinInfo> res = std::make_shared<JoinInfo>();
		std::string tmp = "";
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { res->username = tmp; break;}
					case 1: { res->game_code = atoi(tmp.c_str()); break;}
					case 2: { res->nb_player = atoi(tmp.c_str()); break;}
					default: { res->player_usernames.push_back(tmp); }
				}
				colon_nb++;	
				tmp.clear();
			} else tmp += c;
		}
		res->player_usernames.push_back(tmp);
		return res;
	}


	// returns a struct of a string of the form
	// nb_player|beginner|index=username|index=username|...
	std::shared_ptr<StartInfo> parseStartQuery(){
		std::shared_ptr<StartInfo> res = std::make_shared<StartInfo>();
		int rod_nb = 0;
		int player = 0;
		std::string tmp;

		for (char c : str){
			if (c == '|'){
				switch (rod_nb){
					case 0: {
						res->player_nb = atoi(tmp.c_str());
						res->player_usernames.resize(res->player_nb);
						break; 
					}
					case 1: { res->beginner = atoi(tmp.c_str()); break; }
					default : res->player_usernames[player] = tmp;
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
};


#endif
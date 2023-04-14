#ifndef _GAME_LAUNCHING_PARSER_HPP
#define _GAME_LAUNCHING_PARSER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iostream>


struct StartInfo2 {
	int beginner = 0;
	int player_nb = 0;
	std::vector<std::string> player_usernames;

    StartInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, '|'); colon_nb++) {
            switch (colon_nb) {
                case 0 : player_nb = atoi(word.c_str()); player_usernames.resize(player_nb); break;
                case 1 : beginner = atoi(word.c_str()); break;
                default :
                    int egale_nb = 0;
                    int pos = 0;
                    std::istringstream input2{word};
                    for (std::string word2; std::getline(input2, word2, '='); egale_nb++) {
                        switch (egale_nb) {
                            case 0 : pos = atoi(word2.c_str()); break;
                            case 1 : player_usernames.at(pos) = word2; break;
                        }
                    }
                    break;
            }
        }
    }
}; //todo new
struct StartInfo {
	int beginner;
	int player_nb;
	std::vector<std::string> player_usernames;
};

struct JoinInfo2 {
	std::string username = "Unknown";
	int game_code = 0;
	int nb_player = 0;
	std::vector<std::string> player_usernames;

    JoinInfo2(const std::string &str, bool create) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : username = word; break;
                case 1 : game_code = atoi(word.c_str()); break;
                case 2 : nb_player = atoi(word.c_str()); break;
                default : player_usernames.push_back(word); break;
            }
        }
        if (create) {
            player_usernames.push_back(username);
            nb_player = 1;
        }
    }
}; //todo new
struct JoinInfo {
	std::string username;
	int game_code;
	bool is_fast;
	int start_money;
	int max_players;
	int max_house;
	int max_hotels;
	int max_turns;
	int nb_player;
	std::vector<std::string> player_usernames;
};


class GameLaunchingParser {

	std::string str;

public:

	GameLaunchingParser(std::string str) : str{str} {};


	// returns a struct of a string of the form
	// username:gameCode [string]:[int]
	std::shared_ptr<JoinInfo2> parseCreateQuery2() {
		std::shared_ptr<JoinInfo2> res = std::make_shared<JoinInfo2>(this->str, true);
		return res;
	} // todo new
	std::shared_ptr<JoinInfo> parseCreateQuery() {
		std::shared_ptr<JoinInfo> res = std::make_shared<JoinInfo>();
		std::string tmp;
		int colon_nb = 0;
		res->nb_player = 1;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { res->username = tmp; res->player_usernames.push_back(tmp); break;}
					case 1: { res->game_code = atoi(tmp.c_str()); break;}
					case 2: { res->is_fast = static_cast<bool>(atoi(tmp.c_str())); break;}
					case 3: { res->start_money = atoi(tmp.c_str()); break;}
					case 4: { res->max_players = atoi(tmp.c_str()); break;}
					case 5: { res->max_house = atoi(tmp.c_str()); break;}
					case 6: { res->max_hotels = atoi(tmp.c_str()); break;}
				}
				colon_nb++;
				tmp.clear();
			} else tmp += c;
		}
		res->max_turns = atoi(tmp.c_str());
		return res;		
	}


	// returns a struct of a string of the form
	// username:gameCode:nb_player:{usernames} [string]:[int]:[int]:{[string]}
	std::shared_ptr<JoinInfo2> parseJoinQuery2() {
		std::shared_ptr<JoinInfo2> res = std::make_shared<JoinInfo2>(this->str, false);
		return res;
	} // todo new
	std::shared_ptr<JoinInfo> parseJoinQuery() {
		std::shared_ptr<JoinInfo> res = std::make_shared<JoinInfo>();
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { res->username = tmp; break; }
					case 1: { res->game_code = atoi(tmp.c_str()); break; }
					case 2: { res->is_fast = static_cast<bool>(atoi(tmp.c_str())); break; }
					case 3: { res->start_money = atoi(tmp.c_str()); break; }
					case 4: { res->max_players = atoi(tmp.c_str()); break; }
					case 5: { res->max_house = atoi(tmp.c_str()); break; }
					case 6: { res->max_hotels = atoi(tmp.c_str()); break; }
					case 7: { res->max_turns = atoi(tmp.c_str()); break; }
					case 8: { res->nb_player = atoi(tmp.c_str()); break; }
					default: res->player_usernames.push_back(tmp); break;
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
	std::shared_ptr<StartInfo2> parseStartQuery2(){
		std::shared_ptr<StartInfo2> res = std::make_shared<StartInfo2>(this->str);
		return res;
	} //todo new
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
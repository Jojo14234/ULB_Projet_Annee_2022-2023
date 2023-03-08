#ifndef _GAME_STATE_PARSER_HPP
#define _GAME_STATE_PARSER_HPP

#include <string>
#include <vector>
#include <array>

struct PropertyInformation {
	std::string name;
	int level;
	bool hypotek;
};

struct Informations {
	std::vector<std::array<int, 3>> state; // position, argent, nombre j carte
	std::vector<std::vector<PropertyInformation>> info;
};

class GameStateParser {

	std::string state_str;
	Informations res;
	std::string property_str;

public:
	GameStateParser(std::string game, int player_nb) : state_str{state_str} {
		res.state.resize(player_nb);
		res.info.resize(player_nb);
		parseStateLine();
		parsePropertiesLine();

	};

	void parseStateLine(){
		int player = 0;
		int arg_nb = 0;
		int i = 0;
		res.state.clear();
		std::string tmp;

		for (char c : state_str){
			if (c == ':'){ 
				player = atoi(&tmp[1]);
				tmp.clear();
			} 
			else if (c == '-'){
				tmp.clear();
			}
			else if (c == ',' or c == ';'){
				res.state[player][arg_nb] = atoi(tmp.c_str());
				tmp.clear();
				c == ',' ? arg_nb++ : arg_nb = 0;
			}
			else if (c == '\n'){
				property_str = &state_str[i+1];
				break;
			}
			else {
				tmp += c;
			}
			i++;
		}
	}

	void parsePropertiesLine(){
		int player = 0;
		int arg_nb = 0;
		res.info.clear();
		std::string tmp;
		PropertyInformation pi;

		for (char c : state_str){
			if (c == ':'){ 
				player = atoi(&tmp[1]);
				tmp.clear();
			} 
			else if (c == '-'){
				tmp.clear();
			}
			else if (c == ',' or c == ';'){
				switch (arg_nb) {
					case 0 : {pi.name = tmp; tmp.clear(); break;}
					case 1 : {pi.level = atoi(tmp.c_str()); tmp.clear(); break;}
					case 2 : {(c == 'n') ? pi.hypotek = false : pi.hypotek = true ; tmp.clear(); break;}
					default : break;
				}
				c == ',' ? arg_nb++ : arg_nb = 0;
			}
			else if (c == '.'){
				res.info[player].push_back(pi);
				tmp.clear();
				arg_nb = 0;
			}
			else if (c == '\n'){
				break;
			}
			else {
				tmp += c;
			}
		}
	}

	const Informations& getBufferSplit() const { return res; }
};



#endif
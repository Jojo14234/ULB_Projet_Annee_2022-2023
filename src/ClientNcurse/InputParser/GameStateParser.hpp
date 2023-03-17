#ifndef _GAME_STATE_PARSER_HPP
#define _GAME_STATE_PARSER_HPP

#include <string>
#include <vector>
#include <array>

struct PropertyInformation {
	int owner;
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
	unsigned int index;

public:
	GameStateParser(std::string game) : state_str{game} {};

	int parseIntroLine(){
		char n_player;
		int i = 0;
		while(state_str[i] != ';'){
			n_player = state_str[i];
			i++;
		}
		int n_p = int(n_player) - '0';
		return n_p;

	
	}

	void parseStateLine(int player_nb){
		state_str += ",";
		int player = 0;
		int arg_nb = 0;
		int i = 0;
		index = 0;
		res.state.resize(player_nb);
		res.state.clear();
		std::string tmp;
		while(state_str[index] != '\n'){
			char c = state_str[index];
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
			else{
				tmp += c;
			}
			i++;
			index++;
		}
		
		index++;	
	}
	

	void parsePropertiesLine(int player_nb){
		int player = 0;
		int arg_nb = 0;
		res.info.resize(player_nb);
		res.info.clear();
		std::string tmp;
		PropertyInformation pi;
		while(index < (unsigned int)state_str.size() ){
			char c = state_str[index];
			if (c == ':'){ 
				
				player = atoi(&tmp[1]);
				tmp.clear();
			} 
			else if (c == '-'){
				tmp.clear();
			}
			else if (c == ','){
				switch (arg_nb % 3) {
					case 0 : {pi.name = tmp;tmp.clear(); break;}
					case 1 : {pi.level = atoi(tmp.c_str()); tmp.clear(); break;}
					case 2 : {(c == 'n') ? pi.hypotek = false : pi.hypotek = true ; tmp.clear(); break;}
					default : break;
				}
				pi.owner = player + 1;
				arg_nb++;
			}
			else if (c == ';'){
				if (pi.name != ""){
					res.info[player].push_back(pi);
				}
				
				tmp.clear();
				arg_nb = 0;
			}
			else if (c == '\n'){
				break;
			}
			else {
				tmp += c;
			}
			index++;
		}
	
	}

	const Informations& getBufferSplit() const { return res; }
};



#endif
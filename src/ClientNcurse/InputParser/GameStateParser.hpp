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

struct DiceInformations {
	int first_value;
	int second_value;
	int total_value;
	bool is_double;
	int double_counter; 
};

class GameStateParser {

	std::string str;
	unsigned int index;
	
	Informations res;
	DiceInformations dice;

	void parseStateLine(int player_nb){
		str += ",";
		int player = 0;
		int arg_nb = 0;
		int i = 0;
		index = 0;
		res.state.resize(player_nb);
		res.state.clear();
		std::string tmp;
		while(str[index] != '\n'){
			char c = str[index];
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
		while(index < (unsigned int)str.size() ){
			char c = str[index];
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

public:

	GameStateParser(std::string game) : str{game} {};

	const Informations& parseEndTurnLine(int player_nb){
		this->parseStateLine(player_nb);
		this->parsePropertiesLine(player_nb);
		return res;
	}

	const DiceInformations& parseDiceLine(){
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: {
						dice.first_value = atoi(tmp.c_str());
						break;
					}
					case 1: {
						dice.second_value = atoi(tmp.c_str());
					}
					case 2: {
						dice.total_value = atoi(tmp.c_str());
					}
					case 3: {
						dice.is_double = static_cast<bool>((atoi(tmp.c_str())));
					}
				}
				colon_nb++;	
				tmp.clear();
			} else tmp += c;
		}
		dice.double_counter = atoi(tmp.c_str());
		return dice;
	}

};



#endif
#ifndef _GAME_STATE_PARSER_HPP
#define _GAME_STATE_PARSER_HPP

#include <string>
#include <vector>
#include <array>

struct PropertyInformations {
	std::string name;
	int level;
	bool mortgage;
};

struct PlayerInformations{
	std::string username;
	int position;
	int money;
	int jail_card_nb;
	std::vector<PropertyInformations> properties;
};

struct PlayerInteractProperty{
	int player;
	std::string property_name;
	int player_money;
};


struct DiceInformations {
	int first_value;
	int second_value;
	int total_value;
	bool is_double;
	int double_counter; 
};


struct PlayerPaidPlayerInformations{

};

class GameStateParser {

	std::string str;

	std::vector<PlayerInformations> players;
	PlayerInteractProperty interact;
	DiceInformations dice;

public:

	GameStateParser(std::string game) : str{game} {};

	const std::vector<PlayerInformations>& parseEndTurnLine(int player_nb){
		players.resize(player_nb);
		std::string tmp;
		PropertyInformations p_i;
		int colon_nb = 0;
		int semicolon_nb = 0;
		int player_index = 0;

		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { player_index = atoi(tmp.c_str()); break;}
					case 1: { players[player_index].username = tmp; break;}
					case 2: { players[player_index].position = atoi(tmp.c_str()); break;}
					case 3: { players[player_index].money = atoi(tmp.c_str()); break;}
					case 4: { players[player_index].jail_card_nb = atoi(tmp.c_str()); break;}
					default:{
						p_i.mortgage = static_cast<bool>(atoi(tmp.c_str()));
						players[player_index].properties.push_back(p_i);
						semicolon_nb = 0;
					}
				}
				colon_nb++;
				tmp.clear();
			}
			else if (c == ';'){
				switch (semicolon_nb){
					case 0: { p_i.name = tmp; break;}
					case 1: { p_i.level = atoi(tmp.c_str()); break;}
				}
				semicolon_nb++;
				tmp.clear();
			}
			else if (c == '|'){
				semicolon_nb = 0;
				colon_nb = 0;
				tmp.clear();
			}
			else tmp += c;
		}
		return players;
	}

	const DiceInformations& parseDiceLine(){
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { dice.first_value = atoi(tmp.c_str()); break;}
					case 1: { dice.second_value = atoi(tmp.c_str()); break;}
					case 2: { dice.total_value = atoi(tmp.c_str()); break;}
					case 3: { dice.is_double = static_cast<bool>(atoi(tmp.c_str())); break;}
				}
				colon_nb++;	
				tmp.clear();
			} else tmp += c;
		}
		dice.double_counter = atoi(tmp.c_str());
		return dice;
	}

	const PlayerInteractProperty& parseInteraction(){
		int colon_nb = 0;
		int i = 0;
		std::string tmp;
		while (str[i] != ':' || colon_nb < 1) {
			if (str[i] == ':') {
				interact.player = atoi(tmp.c_str())+1;
				colon_nb++;
				tmp.clear();
			}
			else tmp += str[i]; 
			i++;
		}
		interact.property_name = tmp;
		interact.player_money = atoi(&str[i+1]);
		return interact;
	}

};



#endif
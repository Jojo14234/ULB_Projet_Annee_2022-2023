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
	int amount;
	int loser;
	int loser_money;
	int winner;
	int winner_money;
};


struct PlayerInteractTax{
    std::string tax_name;
    int price;
    int player;
    int player_money;
};


struct PlayerInteractMortgagedCell{
    std::string username;
    std::string owner_username;
};


struct PlayerWonOrLoseMoneyInfo{
	int player;
	int amount;
	int player_money;
};


struct PlayerMoveByCard{
	int player;
	int new_pos;
};


class GameStateParser {

	std::string str;

	std::vector<PlayerInformations> players;
	PlayerInteractProperty interact;
	DiceInformations dice;
	PlayerPaidPlayerInformations payment;
	PlayerInteractTax tax;
	PlayerInteractMortgagedCell mortgaged;
	PlayerWonOrLoseMoneyInfo won_or_lose;
	PlayerMoveByCard move_by_card;
	std::vector<std::string> properties;

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

	const PlayerPaidPlayerInformations& parsePayement(){
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { payment.amount = atoi(tmp.c_str()); break;}
					case 1: { payment.loser = atoi(tmp.c_str()) + 1; break;}
					case 2: { payment.loser_money = atoi(tmp.c_str()); break;}
					case 3: { payment.winner = atoi(tmp.c_str()) + 1; break;}
				}
				colon_nb++;	
				tmp.clear();
			} 
			else tmp += c;
		}
		payment.winner_money = atoi(tmp.c_str());
		return payment;
	}

	const PlayerInteractTax& parseTaxLine() {
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { tax.tax_name = tmp; break;}
					case 1: { tax.price = atoi(tmp.c_str()); break;}
					case 2: { tax.player = atoi(tmp.c_str()) + 1; break;}
				}
				colon_nb++;
				tmp.clear();
			} else tmp += c;
		}
		tax.player_money = atoi(tmp.c_str());
		return tax;
	}

	const PlayerInteractMortgagedCell& parseMortgagedLine() {
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		mortgaged.username = tmp;
		mortgaged.owner_username = &str[i+1];
		return mortgaged;
	}

	const PlayerWonOrLoseMoneyInfo& parseWonOrLoseMoney(){
		int colon_nb = 0;
		int i = 0;
		std::string tmp;
		while (str[i] != ':' || colon_nb < 1) {
			if (str[i] == ':') {
				won_or_lose.player = atoi(tmp.c_str())+1;
				colon_nb++;
				tmp.clear();
			} else tmp += str[i]; 
			i++;
		}
		won_or_lose.amount = atoi(tmp.c_str());
		won_or_lose.player_money = atoi(&str[i+1]);
		return won_or_lose;
	}	

	const PlayerMoveByCard& parsePlayerMoveByCard() {
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		move_by_card.player = atoi(tmp.c_str())+1;
		move_by_card.new_pos = atoi(&str[i+1]);
		return move_by_card;
	}

	std::vector<std::string> parsePropertiesName() {
		std::string tmp;
		for (char c : str){
			if (c == ':') {
				properties.push_back(tmp);
				tmp.clear();
			} else tmp += c;
		}
		return properties;
	}
	
};



#endif
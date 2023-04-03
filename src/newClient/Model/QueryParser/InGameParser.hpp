#ifndef _GAME_STATE_PARSER_HPP
#define _GAME_STATE_PARSER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>


struct BuildSucessInfo {
	std::string name;
	int level;
	bool mortgage;
};

struct GameInfo {
	std::string username;
	int position;
	int money;
	int jail_card_nb;
	std::vector<BuildSucessInfo> properties;
};

struct PlayerMoveInfo {
	int player;
	std::string property_name;
	int player_money;
};

struct RollDiceInfo {
	int first_value;
	int second_value;
	int total_value;
	bool is_double;
	int double_counter; 
};

struct PlayerPaidPlayerInfo {
	int amount;
	int loser;
	int loser_money;
	int winner;
	int winner_money;
};

struct MoveTaxInfo {
    std::string tax_name;
    int price;
    int player;
    int player_money;
};

struct MoveMortgagedInfo {
    std::string username;
    std::string owner_username;
};

struct WonOrLoseMoneyInfo {
	int player;
	int amount;
	int player_money;
};

struct MoveByCardInfo {
	int player;
	int new_pos;
};

struct MoveOnCardCellInfo {
	int player;
	int new_pos;
	std::string description;
};

struct AskForPurchaseInfo {
	std::string cell_name;
	int amount;
};


class InGameParser {

	std::string str;

public:

	InGameParser(std::string game) : str{game} {};

	std::shared_ptr<std::vector<GameInfo>> parseInfosGameQuery(int player_nb) {
		std::shared_ptr<std::vector<GameInfo>> res = std::make_shared<std::vector<GameInfo>>();
		std::string tmp;
		BuildSucessInfo property_info;
		res->resize(player_nb);
		int colon_nb = 0;
		int semicolon_nb = 0;
		int player_index = 0;

		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { player_index = atoi(tmp.c_str()); break;}
					case 1: { res->at(player_index).username = tmp; break;}
					case 2: { res->at(player_index).position = atoi(tmp.c_str()); break;}
					case 3: { res->at(player_index).money = atoi(tmp.c_str()); break;}
					case 4: { res->at(player_index).jail_card_nb = atoi(tmp.c_str()); break;}
					default:{
						property_info.mortgage = static_cast<bool>(atoi(tmp.c_str()));
						res->at(player_index).properties.push_back(property_info);
						semicolon_nb = 0;
					}
				}
				colon_nb++;
				tmp.clear();
			}
			else if (c == ';'){
				switch (semicolon_nb){
					case 0: { property_info.name = tmp; break;}
					case 1: { property_info.level = atoi(tmp.c_str()); break;}
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
		return res;
	}

	std::shared_ptr<RollDiceInfo> parseRollDiceQuery() {
		std::shared_ptr<RollDiceInfo> res = std::make_shared<RollDiceInfo>();
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { res->first_value = atoi(tmp.c_str()); break;}
					case 1: { res->second_value = atoi(tmp.c_str()); break;}
					case 2: { res->total_value = atoi(tmp.c_str()); break;}
					case 3: { res->is_double = static_cast<bool>(atoi(tmp.c_str())); break;}
				}
				colon_nb++;	
				tmp.clear();
			} else tmp += c;
		}
		res->double_counter = atoi(tmp.c_str());
		return res;
	}

	std::shared_ptr<PlayerMoveInfo> parsePlayerMoveQuery() {
		std::shared_ptr<PlayerMoveInfo> res = std::make_shared<PlayerMoveInfo>();
		int colon_nb = 0;
		int i = 0;
		std::string tmp;
		while (str[i] != ':' || colon_nb < 1) {
			if (str[i] == ':') {
				res->player = atoi(tmp.c_str())+1;
				colon_nb++;
				tmp.clear();
			}
			else tmp += str[i]; 
			i++;
		}
		res->property_name = tmp;
		res->player_money = atoi(&str[i+1]);
		return res;
	}

	std::shared_ptr<PlayerPaidPlayerInfo> parsePlayerPaidPlayerQuery() {
		std::shared_ptr<PlayerPaidPlayerInfo> res = std::make_shared<PlayerPaidPlayerInfo>();
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { res->amount = atoi(tmp.c_str()); break;}
					case 1: { res->loser = atoi(tmp.c_str()) + 1; break;}
					case 2: { res->loser_money = atoi(tmp.c_str()); break;}
					case 3: { res->winner = atoi(tmp.c_str()) + 1; break;}
				}
				colon_nb++;	
				tmp.clear();
			} 
			else tmp += c;
		}
		res->winner_money = atoi(tmp.c_str());
		return res;
	}

	std::shared_ptr<MoveTaxInfo> parseMoveTaxQuery() {
		std::shared_ptr<MoveTaxInfo> res = std::make_shared<MoveTaxInfo>();
		std::string tmp;
		int colon_nb = 0;
		for (char c : str){
			if (c == ':'){
				switch (colon_nb){
					case 0: { res->tax_name = tmp; break;}
					case 1: { res->price = atoi(tmp.c_str()); break;}
					case 2: { res->player = atoi(tmp.c_str()) + 1; break;}
				}
				colon_nb++;
				tmp.clear();
			} else tmp += c;
		}
		res->player_money = atoi(tmp.c_str());
		return res;
	}

	std::shared_ptr<MoveMortgagedInfo> parseMoveMortgagedQuery() {
		std::shared_ptr<MoveMortgagedInfo> res = std::make_shared<MoveMortgagedInfo>();
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->username = tmp;
		res->owner_username = &str[i+1];
		return res;
	}

	std::shared_ptr<WonOrLoseMoneyInfo> parseWonOrLoseMoneyQuery() {
		std::shared_ptr<WonOrLoseMoneyInfo> res = std::make_shared<WonOrLoseMoneyInfo>();
		int colon_nb = 0;
		int i = 0;
		std::string tmp;
		while (str[i] != ':' || colon_nb < 1) {
			if (str[i] == ':') {
				res->player = atoi(tmp.c_str())+1;
				colon_nb++;
				tmp.clear();
			} else tmp += str[i]; 
			i++;
		}
		res->amount = atoi(tmp.c_str());
		res->player_money = atoi(&str[i+1]);
		return res;
	}	

	std::shared_ptr<MoveByCardInfo> parseMoveByCardQuery() {
		std::shared_ptr<MoveByCardInfo> res = std::make_shared<MoveByCardInfo>();
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->player = atoi(tmp.c_str())+1;
		res->new_pos = atoi(&str[i+1]);
		return res;
	}

	std::shared_ptr<std::vector<std::string>> parseBuildOrSellQuery() {
		std::shared_ptr<std::vector<std::string>> res = std::make_shared<std::vector<std::string>>();
		std::string tmp;
		for (char c : str){
			if (c == ':') {
				res->push_back(tmp);
				tmp.clear();
			} else tmp += c;
		}
		return res;
	}
	
	std::shared_ptr<MoveOnCardCellInfo> parseMoveOnCardCellQuery() {
		std::shared_ptr<MoveOnCardCellInfo> res = std::make_shared<MoveOnCardCellInfo>();
		int colon_nb = 0;
		int i = 0;
		std::string tmp;
		while (str[i] != ':' || colon_nb < 1) {
			if (str[i] == ':') {
				res->player = atoi(tmp.c_str())+1;
				colon_nb++;
				tmp.clear();
			} else tmp += str[i]; 
			i++;
		}
		res->new_pos = atoi(tmp.c_str());
		res->description = &str[i+1];
		return res;
	}	

	std::shared_ptr<AskForPurchaseInfo> parseAskForPurchaseQuery() {
		std::shared_ptr<AskForPurchaseInfo> res = std::make_shared<AskForPurchaseInfo>();
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->cell_name = tmp;
		res->amount = atoi(&str[i+1]);
		return res;
	}

	std::shared_ptr<BuildSucessInfo> parseBuildSuccesQuery() {
		std::shared_ptr<BuildSucessInfo> res = std::make_shared<BuildSucessInfo>();
		int colon_nb = 0;
		int i = 0;
		std::string tmp;
		while (str[i] != ':' || colon_nb < 1) {
			if (str[i] == ':') {
				res->name = tmp;
				colon_nb++;
				tmp.clear();
			} else tmp += str[i]; 
			i++;
		}
		res->level = atoi(tmp.c_str());
		res->mortgage = static_cast<bool>(atoi(&str[i+1]));
		return res;
	}

};



#endif
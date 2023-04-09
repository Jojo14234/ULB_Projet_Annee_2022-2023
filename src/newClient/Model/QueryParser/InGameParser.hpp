#ifndef _GAME_STATE_PARSER_HPP
#define _GAME_STATE_PARSER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iostream>

struct BuildSuccessInfo2 {
	std::string name = "Unknown";
	int level = 0;
	bool mortgage = false;

    BuildSuccessInfo2(const std::string& str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : name = word; break;
                case 1 : level = atoi(word.c_str()); break;
                case 2 : mortgage = static_cast<bool>(atoi(word.c_str())); break;
                default : break;
            }
        }
    }
}; // todo new
struct BuildInfo {
	std::string name;
	int level;
	bool mortgage;
};

struct GameInfo2 {
	std::string username = "Unknown";
	int position = 0;
	int money = 0;
	int jail_card_nb = 0;
	std::vector<BuildSuccessInfo2> properties;

    GameInfo2(const std::string & str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : username = word; break;
                case 1 : money = atoi(word.c_str()); break;
                case 2 : jail_card_nb = atoi(word.c_str()); break;
                case 3 : properties.push_back(BuildSuccessInfo2{word}); break;
                default: break;
            }
        }
    }
}; // todo new
struct GameInfo {
	std::string username;
	int position;
	int money;
	int jail_card_nb;
	std::vector<BuildInfo> properties;
};

struct GameInfoList{
    std::vector<GameInfo2> infos;

    GameInfoList(const std::string &str) {
        std::istringstream input{str};
        for (std::string word; std::getline(input, word, '|');) {
            infos.push_back(GameInfo2{word});
        }
    }
}; // todo new

struct PlayerMoveInfo2 {
	int player = 0;
	std::string property_name = "None";
	int player_money = 0;

    PlayerMoveInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : player = atoi(word.c_str()); break;
                case 1 : property_name = word; break;
                case 2 : player_money = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
    std::string to_string() {
        std::string str = "";
        if (property_name == "Prison") {str += "Vous visitez la prison.";}
        else if (property_name == "Start") {str += "Vous arrivez sur la case départ.";}
        else if (property_name == "Parc") {str += "Vous vous baladez dans le parc gratuit.";}
        return str;
    }
}; // todo new
struct PlayerMoveInfo {
	int player;
	std::string property_name;
	int player_money;
};

struct RollDiceInfo2 {
    int first_value = 0;
    int second_value = 0;
    int total_value = 0;
    bool is_double = false;
    int double_counter = 0;

    RollDiceInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0: first_value = atoi(word.c_str()); break;
                case 1: second_value = atoi(word.c_str()); break;
                case 2: total_value = atoi(word.c_str()); break;
                case 3: is_double = static_cast<bool>(atoi(word.c_str())); break;
                case 4: double_counter = atoi(word.c_str()); break;
                default: break;
            }
        }
    }
    std::string to_text(bool isActualPlayer, std::string Username = "actuel") {
        std::string str = (isActualPlayer) ? "Vous avez " : "Le joueur [" + Username + "] a ";
        str += "obtenu un " + std::to_string(first_value) + " et un " + std::to_string(second_value);
        return str;
    }
}; // todo new
struct RollDiceInfo {
    bool operator==(RollDiceInfo2* other) {
        if (first_value != other->first_value) {std::cout << "first val" << std::endl;}
        if (second_value != other->second_value) {std::cout << "Second val" << std::endl;}
        if (total_value != other->total_value) {std::cout << "Total val" << std::endl;}
        if (is_double != other->is_double) {std::cout << "isdouble val" << std::endl;}
        if (double_counter != other->double_counter) {std::cout << "double_counter val" << std::endl;}
        return true;
    }
    bool operator==(RollDiceInfo2 &other) {
        if (first_value != other.first_value) {std::cout << "first val" << std::endl;}
        if (second_value != other.second_value) {std::cout << "Second val" << std::endl;}
        if (total_value != other.total_value) {std::cout << "Total val" << std::endl;}
        if (is_double != other.is_double) {std::cout << "isdouble val" << std::endl;}
        if (double_counter != other.double_counter) {std::cout << "double_counter val" << std::endl;}
        return true;
    }
	int first_value;
	int second_value;
	int total_value;
	bool is_double;
	int double_counter; 
};

struct PlayerPaidPlayerInfo2 {
	int amount = 0;
	int loser = 0;
	int loser_money = 0;
	int winner = 0;
	int winner_money = 0;
    PlayerPaidPlayerInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : amount = atoi(word.c_str()); break;
                case 1 : loser = atoi(word.c_str()) + 1; break;
                case 2 : loser_money = atoi(word.c_str()); break;
                case 3 : winner = atoi(word.c_str()) + 1; break;
                case 4 : winner_money = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
    std::string to_string(bool isActualPlayer, std::string UsernamePay, std::string UsernameReceive) {
        std::string str = (isActualPlayer) ? "Vous devez " : UsernamePay + " vous doit ";
        str += std::to_string(amount);
        str = (isActualPlayer) ? str + " à " + UsernameReceive : str;
        return str;
    }
}; // todo new
struct PlayerPaidPlayerInfo {
	int amount;
	int loser;
	int loser_money;
	int winner;
	int winner_money;
};

struct MoveTaxInfo2 {
    std::string tax_name = "None";
    int price = 0;
    int player = 0;
    int player_money = 0;

    MoveTaxInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : tax_name = word; break;
                case 1 : price = atoi(word.c_str()); break;
                case 2 : player_money = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
    std::string to_string(bool isActualPlayer, std::string username) {
        std::string str = (isActualPlayer) ? "Vous etes arrive " : username + " est arrivé ";
        str += "sur la taxe " + tax_name + " et paye sa taxe à hauteur de " + std::to_string(price) + "$.";
        return str;
    }
}; // todo new
struct MoveTaxInfo {
    std::string tax_name;
    int price;
    int player;
    int player_money;
};

struct MoveMortgagedInfo2 {
    std::string username = "Unknown";
    std::string owner_username = "Unknown";

    MoveMortgagedInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : username = word; break;
                case 1 : owner_username = word; break;
                default : break;
            }
        }
    }
    std::string to_string() {
        std::string str = username + " est tombe sur la propriete de " + owner_username + " qui est actuellement en hypoteque.";
        return str;
    }
}; // todo new
struct MoveMortgagedInfo {
    std::string username;
    std::string owner_username;
};

struct WonOrLoseMoneyInfo2 {
	int player = 0;
	int amount = 0;
	int player_money = 0;

    WonOrLoseMoneyInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : player = atoi(word.c_str()); break;
                case 1 : amount = atoi(word.c_str()); break;
                case 2 : player_money = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
}; // todo new
struct WonOrLoseMoneyInfo {
	int player;
	int amount;
	int player_money;
};

struct MoveByCardInfo2 {
	int player = 0;
	int new_pos = 0;

    MoveByCardInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : player = atoi(word.c_str()); break;
                case 1 : new_pos = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
}; // todo new
struct MoveByCardInfo {
	int player;
	int new_pos;
};

struct MoveOnCardCellInfo2 {
	int player = 0;
	int new_pos = 0;
	std::string description = "None";

    MoveOnCardCellInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : player = atoi(word.c_str()); break;
                case 1 : new_pos = atoi(word.c_str()); break;
                case 3 : description = word; break;
                default : break;
            }
        }
    }
}; // todo new
struct MoveOnCardCellInfo {
	int player;
	int new_pos;
	std::string description;
};

struct AskForPurchaseInfo2 {
	std::string cell_name = "None";
	int amount = 0;

    AskForPurchaseInfo2(const std::string &str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : cell_name = word; break;
                case 1 : amount = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
}; // todo new
struct AskForPurchaseInfo {
	std::string cell_name;
	int amount;
};

struct BuildOrSellList {
    std::vector<std::string> properties;

    BuildOrSellList(const std::string &str) {
        std::istringstream input{str};
        for (std::string word; std::getline(input, word, ':');) {
            properties.push_back(word);
        }
    }
};

struct ExchangeInfo {
	std::vector<std::vector<std::string>> player_properties;

	ExchangeInfo(const std::string &str, int nb_player) {
		player_properties.resize(nb_player);
		int player_index;
		std::string tmp = "";

		for (char c : str) {
			if (c == '=') { player_index = atoi(tmp.c_str()); tmp.clear(); }
			else if (c == '|') { tmp.clear(); }
			else if (c == ':') { player_properties.at(player_index).push_back(tmp); tmp.clear(); }
			else tmp += c;
		}
	}
};

class InGameParser {

	std::string str;

public:

	InGameParser(std::string game) : str{game} {};

	std::shared_ptr<GameInfoList> parseInfosGameQuery2() {
		std::shared_ptr<GameInfoList> res = std::make_shared<GameInfoList>(this->str);
		return res;
	} //todo new
	std::shared_ptr<std::vector<GameInfo>> parseInfosGameQuery(int player_nb) {
		std::shared_ptr<std::vector<GameInfo>> res = std::make_shared<std::vector<GameInfo>>();
		std::string tmp;
		BuildInfo property_info;
		res->resize(player_nb);
		int colon_nb = 0;
		int semicolon_nb = 0;
		int player_index = 0;

		for (char c : str) {
			if (c == ':') {
				switch (colon_nb) {
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
				switch ( semicolon_nb ) {
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

	std::shared_ptr<RollDiceInfo2> parseRollDiceQuery2() {
        std::shared_ptr<RollDiceInfo2> res2 = std::make_shared<RollDiceInfo2>(this->str);
        return res2;

    } // todo new
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

    std::shared_ptr<PlayerMoveInfo2> parsePlayerMoveQuery2() {
        std::shared_ptr<PlayerMoveInfo2> res2 = std::make_shared<PlayerMoveInfo2>(this->str);
        return res2;
    } //todo new
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

	std::shared_ptr<PlayerPaidPlayerInfo2> parsePlayerPaidPlayerQuery2() {
        std::shared_ptr<PlayerPaidPlayerInfo2> res2 = std::make_shared<PlayerPaidPlayerInfo2>(this->str);
        return res2;
    } // todo new
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

	std::shared_ptr<MoveTaxInfo2> parseMoveTaxQuery2() {
        std::shared_ptr<MoveTaxInfo2> res = std::make_shared<MoveTaxInfo2>(this->str);
        return res;
    } // todo new
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

	std::shared_ptr<MoveMortgagedInfo2> parseMoveMortgagedQuery2() {
        std::shared_ptr<MoveMortgagedInfo2> res = std::make_shared<MoveMortgagedInfo2>(this->str);
        return res;

    } // todo new
	std::shared_ptr<MoveMortgagedInfo> parseMoveMortgagedQuery() {
		std::shared_ptr<MoveMortgagedInfo> res = std::make_shared<MoveMortgagedInfo>();
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->username = tmp;
		res->owner_username = &str[i+1];
		return res;
	}

	std::shared_ptr<WonOrLoseMoneyInfo2> parseWonOrLoseMoneyQuery2() {
        std::shared_ptr<WonOrLoseMoneyInfo2> res = std::make_shared<WonOrLoseMoneyInfo2>(this->str);
        return res;
    } // todo new
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

	std::shared_ptr<MoveByCardInfo2> parseMoveByCardQuery2() {
        std::shared_ptr<MoveByCardInfo2> res = std::make_shared<MoveByCardInfo2>(this->str);
        return res;
    } // todo new
	std::shared_ptr<MoveByCardInfo> parseMoveByCardQuery() {
		std::shared_ptr<MoveByCardInfo> res = std::make_shared<MoveByCardInfo>();
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->player = atoi(tmp.c_str())+1;
		res->new_pos = atoi(&str[i+1]);
		return res;
	}

	std::shared_ptr<BuildOrSellList> parseBuildOrSellQuery2() {
        std::shared_ptr<BuildOrSellList> res = std::make_shared<BuildOrSellList>(this->str);
        return res;
    } // todo new
	std::shared_ptr<std::vector<std::string>> parseSelectPropertyQuery() {
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
	
	std::shared_ptr<MoveOnCardCellInfo2> parseMoveOnCardCellQuery2() {
        std::shared_ptr<MoveOnCardCellInfo2> res = std::make_shared<MoveOnCardCellInfo2>(this->str);
        return res;
    } //todo new
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

	std::shared_ptr<AskForPurchaseInfo2> parseAskForPurchaseQuery2() {
        std::shared_ptr<AskForPurchaseInfo2> res = std::make_shared<AskForPurchaseInfo2>(this->str);
        return res;
    } // todo new
	std::shared_ptr<AskForPurchaseInfo> parseAskForPurchaseQuery() {
		std::shared_ptr<AskForPurchaseInfo> res = std::make_shared<AskForPurchaseInfo>();
		int i = 0;
		std::string tmp;
		while (str[i] != ':' ) { tmp += str[i]; i++; }
		res->cell_name = tmp;
		res->amount = atoi(&str[i+1]);
		return res;
	}

	std::shared_ptr<BuildSuccessInfo2> parseBuildSuccessQuery2() {
        std::shared_ptr<BuildSuccessInfo2> res2 = std::make_shared<BuildSuccessInfo2>(this->str);
        return res2;
    } // todo new
	std::shared_ptr<BuildInfo> parseBuildQuery() {
		std::shared_ptr<BuildInfo> res = std::make_shared<BuildInfo>();
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
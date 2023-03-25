#ifndef _INFORMATION_BOX_HPP_
#define _INFORMATION_BOX_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>

#include "../Object/TextBox.hpp"

class InformationBox: public TextBox{

	int player_nb = 0;
	std::vector<std::string> usernames;
	std::vector<int> player_money;
	int money = 0;
	int nb_card = 0;

public:

	InformationBox(ObjectInfo info):
		AbstractViewObject{info}, 
		Box{info},
		Text{info, {}, false},
		TextBox{info, {}, false}{}

	void addPlayerLine(std::string username){
		this->addText(std::to_string(player_nb+1) + ": " + username);
		usernames.push_back(username);
		player_nb++;
	}

	void setPlayersInGame(std::vector<std::string>& players){
		this->clearAllText();
		for (auto& player : players) this->addText("- " + player); 
	}

	void setPlayerInfo(int player, int money, int nb_card){
		this->money = money;
		this->nb_card = nb_card;
		this->setText(std::to_string(player) + ": " +
					  usernames[player-1] +  " - " +
					  std::to_string(money) + "$, " +
					  std::to_string(nb_card) + " cartes prisons"
					  , player-1);
	}

	void changePlayerMoney(int player, int money){
		this->money = money;
		this->setText(std::to_string(player) + ": " +
					  usernames[player-1] +  " - " +
					  std::to_string(money) + "$, " +
					  std::to_string(this->nb_card) + " cartes prisons"
					  , player-1);
	}

	void addCardToPlayer(int player){
		this->nb_card++;
		this->setText(std::to_string(player) + ": " +
					  usernames[player-1] +  " - " +
					  std::to_string(this->money) + "$, " +
					  std::to_string(nb_card) + " cartes prisons"
					  , player-1);
	}

	void removeCardToPlayer(int player){
		this->nb_card--;
		this->setText(std::to_string(player) + ": " +
					  usernames[player-1] +  " - " +
					  std::to_string(this->money) + "$, " +
					  std::to_string(nb_card) + " cartes prisons"
					  , player-1);
	}
};

#endif

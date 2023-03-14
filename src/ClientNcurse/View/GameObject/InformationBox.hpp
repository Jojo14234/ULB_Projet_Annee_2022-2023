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
	// int jcard = 0; // for now, useless
	int money = 1500;


public:
	InformationBox(ObjectInfo info):
		AbstractViewObject{info}, 
		Box{info},
		Text{info, {}, false},
		TextBox{info, {}, false}{}

	/*InformationBox(ObjectInfo info, int player_nb, std::vector<std::string> usernames):
		InformationBox(info){
			player_nb = player_nb;
			usernames = usernames;
		}*/

	void addPlayer(std::string username){
		this->addText(std::to_string(player_nb+1) + ": " + username);
		usernames.push_back(username);
		player_nb++;
	}

	void setMoney(int player, int money){
		this->setText(std::to_string(player) + ": " + usernames[player-1] +  " = " + std::to_string(money), player-1);
	}
	
	/*void setAllPlayerMoney( int money ) {
        for (int i = 1; i <= player_nb; i++){ setMoney(i,money); }
    }*/

	/*void setNumberCard( int new_jcard ) {
		setText("Cartes pour sortir de prison : " + std::to_string(new_jcard), player_nb + 1);
	}*/

};

#endif

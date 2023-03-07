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

	int n_player;
	std::vector<std::string> player_name;
	std::vector<int> player_money;
	// int jcard = 0; // for now, useless
	int money = 1500;


public:
	InformationBox(ObjectInfo info, int n_player, std::vector<std::string> player_name):
        AbstractViewObject{info}, TextBox{info,{"Cartes pour sortir de prison :"},false},
		Box{info}, Text{info,{"Cartes pour sortir de prison : 0"},false}, n_player{n_player}, player_name{player_name}
        {
            addText("");
			for ( int i = 1; i <= n_player; i++ ) {
                addText(std::to_string(i) +":" + player_name[i-1] + " = " + std::to_string(money));
            }
		}
	void setMoney( int player,int money ) {
		setText(std::to_string(player) + ":" + player_name[player-1] + " = " + std::to_string(money),player+1);
    }
	
	void setAllPlayerMoney( int money ) {
        for (int i = 1; i <= n_player; i++){ setMoney(i,money); }
    }

	void setNumberCard( int new_jcard ) {
		setText("Cartes pour sortir de prison : " + std::to_string(new_jcard),0);
	}

	

};

#endif

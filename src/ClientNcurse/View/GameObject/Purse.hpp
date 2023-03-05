#ifndef _PURSE_HPP_
#define _PURSE_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>

#include "../Object/Box.hpp"

class Purse: public TextBox{
    int n_player;
    int pos_player = 1;
    int pos_money = 4;
    public:
        Purse(int n_player, ObjectInfo info): n_player(n_player), TextBox{info,{"bourse"},false},
AbstractViewObject(info),Box(info),Text(info,{"bourse"},false){
            for (int i = 1; i <= n_player; i++){
                addText(std::to_string(i));}}
        void setMoney(int player,int money){
            setText(std::to_string(player) + " : " + std::to_string(money),player);}
        void setAllPlayerMoney(int money){
            for (int i = 1; i <= n_player; i++){setMoney(i,money);}}
};


#endif
#ifndef _DRAWMONEY_HPP_
#define _DRAWMONEY_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>

#include "common.h"

//class for the money zone
class DrawMoney{
    WINDOW* money_zone;
    int startmoney;  //money when the game is started
    int nplayer;   
    Point pos{80,10};
    Point size{15,9};
    int pos_player = 1;  //position(x) in the cell where we print the players
    int pos_money = 4;   //position(x) in the cell where we print money

    public:
        DrawMoney(int nplayer, int startmoney);
        void changeMoney(int player, int money);
};

#endif
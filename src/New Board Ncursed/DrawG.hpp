#ifndef _DRAWGAME_HPP_
#define _DRAWGAME_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>

#include "DrawBoard.hpp"
#include "DrawChat.hpp"
#include "DrawDice.hpp"
#include "DrawMoney.hpp"
#include "common.h"

class DrawGame{
    //creat a gameboard
    DrawBoard board;
    int n_player;
    int key;
    bool flag = true;
    
    public: 
        DrawGame(int n_player);
        void printDice();
     
};

#endif
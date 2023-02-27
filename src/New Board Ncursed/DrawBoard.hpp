#ifndef _DRAWBOARD_HPP_
#define _DRAWBOARD_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>

#include "common.h"
 

//Class representing the gameboard with the different game spaces and the spaces for the cards.
class DrawBoard{
    static const int col_nb = 11; 
    static const int line_nb = 11; 
    static const int board_box_nb = col_nb * line_nb; 
    static const int gamebox_nb = 40;

    int n_player; //number of players in game

    WINDOW *board[board_box_nb];  //box_nb number of windows for gameboxes
    WINDOW *cardcases[2];  //box for cards (luck and community)
    WINDOW *legend; //window for the legend's box

    const vector<int> listofcell {0,1,2,3,4,5,6,7,8,9,10,21,32,43,54,65,76,87,98,109,120,
    119,118,117,116,115,114,113,112,111,110,99,88,77,66,55,44,33,22,11};  //vector to convert a gamebox into a board box
    vector<string> cellname; //vector of names of each cells

    //size of a cell
    int height = 5; 
    int width = 11;
    int posplayer = 2; //line on the window for players
    int posbuilding = 3; //line on the window for buildings

    const Point legend_pos {25,35};
    const Point legend_size {16,7};
    Point pos_text1 {1,1};
    Point pos_text2{1,2};
    Point pos_text3 {1,3};
    Point pos_text4 {1,4};

    const Point luckycasepos {20,10};
    const Point commucasepos {65, 38};
    Point cardcasesize {30,7};
    Point pos_text5{9,3};
    Point pos_text6{5,3};

    public: 
        DrawBoard(){};
        void setNplayer(int nplayer);
        vector<string> getCellName(); 
        void initBoard();
        void drawBoard(int n_case);
        void createBoard();
        void setBoxName();
        void destroyBoard();

        void createCardCase();
        void text();
        void createLegend();

        void setPlayer(int cell, int player);
        void unsetPlayer(int cell,int player);
        void clearBuilding(int cell);
        void setPurchased(int cell);
        void setHouse(int cell,int n_house);
        void setHotel(int cell);
        


        
};

#endif
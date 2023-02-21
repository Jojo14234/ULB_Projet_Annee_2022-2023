#ifndef BOARD_CREATOR_H
#define BOARD_CREATOR_H

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>

#include "common.h"
 

using namespace std;
class BoardCreator{
    WINDOW *board[121];
    WINDOW *cardcases[2];
    WINDOW* win;
  

    char input[30];
    int i = 1;
 
    const int  n_cell = 40;
    int n_player;

    const vector<int> listofcell {0,1,2,3,4,5,6,7,8,9,10,21,32,43,54,65,76,87,98,109,120,
    119,118,117,116,115,114,113,112,111,110,99,88,77,66,55,44,33,22,11};
    vector<string> cellname;

    int size = 11;
    int height = 5;
    //int width = 9;
    int width = 11;

    //const Point legend_pos {15,35};
    const Point legend_pos {25,35};
    const Point legend_size {16,7};
    Point pos_text1 {1,1};
    Point pos_text2{1,2};
    Point pos_text3 {1,3};
    Point pos_text4 {1,4};

    //const Point luckycasepos {15,10};
    //const Point commucasepos {55, 38};
    const Point luckycasepos {20,10};
    const Point commucasepos {65, 38};
    Point cardcasesize {30,7};
    Point pos_text5{9,3};
    Point pos_text6{5,3};


    int posplayer = 2;

    public:

        BoardCreator(int n_player);
        void initBoard();
        void createBoard();
        void destroyBoard();
        void drawBoard(int n_case);

        void createCardCase();
        void text();
        void legend();
        vector<string> getCellName();

        void createZone();
        void writeText();


        void setPlayer(int cell, int player);
        void unsetPlayer(int cell,int player);
        void setHouse(int cell);
        void unsetHouse(int cell);
        void setHotel(int cell);
        void unsetHotel(int cell);


};

#endif
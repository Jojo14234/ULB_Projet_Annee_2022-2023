#ifndef _DRAWDICE_HPP_
#define _DRAWDICE_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>

#include "common.h"

//class for printing the dice
class DrawDice{
    Point pos;
    Point size {5,3};
    WINDOW* dice;
    int number = 0;

    public:
        DrawDice(Point pos):pos{pos}{}
        void setDice(int n);
        void drawDice();


};


#endif
#ifndef _DRAWINFO_HPP_
#define _DRAWINFO_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <unistd.h>

#include "common.h"


//class to write a zone for different player/game's action
class DrawInfo{
    WINDOW* win;
    WINDOW* borderwin;
    Point win_size{60,10};
    Point win_loc{126,30};
    public:
        DrawInfo();
        void printText(string text);



};

#endif
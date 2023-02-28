#ifndef _DRAWCHAT_HPP_
#define _DRAWCHAT_HPP_


#include <stdlib.h>
#include <ncurses.h>
#include <vector>

#include "common.h"



class DrawChat{
    WINDOW* chat;
    WINDOW* chat_border;
    char input[30];
    int line = 1; //the first line where the text is written
    Point chat_size { 60, 25};
    Point chat_pos {125,2};
    public:
        DrawChat();
        void writeText();
        int getLine();
        WINDOW* getWin();
};

#endif
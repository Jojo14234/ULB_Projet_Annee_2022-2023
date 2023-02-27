#ifndef _DRAWCHOICE_HPP_
#define _DRAWCHOICE_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>


#include "common.h"

//class to create a window with different choice and user can choose between the choices
class DrawChoice{
    WINDOW* choicewin;
    Point choice_size{62,5};
    Point choice_pos{125,41};
    int n_choice;
    int highlight = 0;
    vector<string> choices;
    int choice;
    public:
        DrawChoice(int n_choice,vector<string> choices);
        string getChoice();
        void delChoice();
};


#endif


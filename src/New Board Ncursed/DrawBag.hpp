#ifndef _DRAWBAG_HPP_
#define _DRAWBAG_HPP_


#include <stdlib.h>
#include <ncurses.h>
#include <vector>

#include "common.h"


//class to define a zone where we put  card  for go out jail
class DrawBag{
    WINDOW* bag;
    Point size_bag {62,5};
    Point pos_bag {125,47};
    int n_cards = 0;
    public:
        DrawBag();
        void setJCardNumber(int n);


};

#endif
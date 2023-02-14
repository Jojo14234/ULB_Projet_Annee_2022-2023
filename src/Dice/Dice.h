#ifndef DICE_H
#define DICE_H

#include "Die.h"

class Dice{
    Die dice1;
    Die dice2;
    int double_counter;
    public:
        Dice();
        void roll();
        int getDice1();
        int getDice2();
        int getDoubleCounter();
        bool isDouble();


};


#endif
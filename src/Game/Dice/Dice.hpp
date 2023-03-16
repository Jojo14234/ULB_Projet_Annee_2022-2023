#ifndef DICE_H
#define DICE_H

#include "Die.hpp"

class Dice{
    Die dice1;
    Die dice2;
    int result;
    int double_counter;
public:
    Dice();
    int roll();

    int getResults() const;
    int getDice1();
    int getDice2();
    int getDoubleCounter() const;
    void resetDoubleCounter();
    bool isDouble() const;

};


#endif

#include "Dice.hpp"

Dice::Dice(){}

int Dice::roll(){
    dice1.roll();
    dice2.roll();
    double_counter = dice1.getResult() + dice2.getResult();
    return double_counter;
}

int Dice::getDice1(){
    return dice1.getResult();
}

int Dice::getDice2(){
    return dice2.getResult();
}

int Dice::getDoubleCounter(){
    return double_counter;
}

bool Dice::isDouble(){
    if (dice1.getResult() == dice2.getResult()){
        return true;
    }
    return false;
}
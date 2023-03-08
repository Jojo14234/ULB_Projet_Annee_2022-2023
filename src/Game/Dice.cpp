#include "Dice.hpp"

Dice::Dice() {}

int Dice::roll(){
    dice1.roll();
    dice2.roll();
    result = dice1.getResult() + dice2.getResult();
    if (dice1.getResult() == dice2.getResult()){
        double_counter++;
    }
    result = 1; //TODO SUPPRIMER
    return result;
}

int Dice::getResults(){
    return result;
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

void Dice::resetDoubleCounter() {
    double_counter = 0;
}

bool Dice::isDouble(){
    if (dice1.getResult() == dice2.getResult()){
        return true;
    }
    return false;
}
#include "Dice.hpp"

Dice::Dice() {}

int Dice::roll() {
    result = dice1.roll() + dice2.roll();
    this->result = 1;
    if ( dice1.getResult() == dice2.getResult() ) { double_counter++; }
    return result;
}

int Dice::getResults() const    { return result; }
int Dice::getDice1()            { return dice1.getResult(); }
int Dice::getDice2()            { return dice2.getResult(); }
int Dice::getDoubleCounter() const { return double_counter; }
void Dice::resetDoubleCounter() { double_counter = 0; }
bool Dice::isDouble() const     { return dice1.getResult() == dice2.getResult(); }
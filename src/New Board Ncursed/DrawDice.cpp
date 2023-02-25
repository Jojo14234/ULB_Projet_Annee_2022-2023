#include "DrawDice.hpp"


//print the dice
void DrawDice::drawDice(){
    dice = newwin(size.y,size.x, pos.y,pos.x);
    box(dice,0,0);
    if (number != 0){
        mvwprintw(dice,1,2,to_string(number).c_str());
    }
    wrefresh(dice);
}

//define the number of dice
void DrawDice::setDice(int n){
    number = n;
    drawDice();
}
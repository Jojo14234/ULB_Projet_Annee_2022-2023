#include "DrawBag.hpp"

DrawBag::DrawBag(){
    bag = newwin(size_bag.y , size_bag.x,  pos_bag.y ,  pos_bag.x);
    box(bag,0,0);
    mvwprintw(bag,1,1, "Cartes pour sortir de prison : %s" ,to_string(n_cards).c_str());
    wrefresh(bag);
}


//method th change the number of jail card in the bag
void DrawBag::setJCardNumber(int n){
    n_cards = n;
    mvwprintw(bag,1,1, "Cartes pour sortir de prison : %s" ,to_string(n_cards).c_str());
    wrefresh(bag);
}
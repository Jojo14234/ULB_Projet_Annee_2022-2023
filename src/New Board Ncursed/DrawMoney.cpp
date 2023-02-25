#include"DrawMoney.hpp"


DrawMoney::DrawMoney(int nplayer, int startmoney):nplayer{nplayer}, startmoney{startmoney}{
    money_zone = newwin(size.y,size.x,pos.y,pos.x);
    box(money_zone,0,0);
    mvwprintw(money_zone,1,4,"bourse");

    //initialize the zone whe the game start
    for (int i = 1; i <= nplayer; i++){
        mvwprintw(money_zone,i+1,pos_player,to_string(i).c_str());
        mvwprintw(money_zone,i+1,2,":");
        mvwprintw(money_zone,i+1,4,to_string(startmoney).c_str());
    }
    wrefresh(money_zone);
}


//change the money zone 
void DrawMoney::changeMoney(int player, int money){
    for (int i = pos_money; i < size.x - 1; i++){
        mvwprintw(money_zone,player+1,i," ");
    }
    mvwprintw(money_zone,player+1,pos_money,to_string(money).c_str());
    wrefresh(money_zone);
}
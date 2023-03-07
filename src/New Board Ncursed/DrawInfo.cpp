#include "DrawInfo.hpp"


//initialize zone
DrawInfo::DrawInfo(){
    win = newwin(win_size.y,win_size.x, win_loc.y, win_loc.x);
    borderwin = newwin(win_size.y+2,win_size.x+2, win_loc.y-1, win_loc.x-1);
    box(borderwin,0,0);
    scrollok(win,true);
    wrefresh(borderwin);

}


//write text (a action) in zone
void DrawInfo::printText(string text){
    wprintw(win,"==>");
    wprintw(win,"%s\n",text.c_str());
    sleep(1);
    wrefresh(win);
}
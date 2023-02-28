#include <stdlib.h>
#include <ncurses.h>
#include <vector>


#include "common.h"

using namespace std;

class ZoneText{
    Point size {8,15};
    Point pos {10,10};
    WINDOW* zone;
    public:
        ZoneText(){};
        void initZone();
        void initWindow();


};


void ZoneText::initWindow(){
    zone = newwin( size.y , size.x , pos.y , pos.x);
    box(zone,0,0);
    
    wrefresh(zone);
}

void ZoneText::initZone(){
    initscr();
    initWindow();
    
    getch(); 
    endwin();  
}

int main(){
    Zon
}


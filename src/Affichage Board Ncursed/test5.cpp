#include <stdlib.h>
#include <ncurses.h>
#include <vector>

#include "common.h"




using namespace std;
void zone(){
    initscr();

    noecho();

    // Activation du curseur
    curs_set(1);


    WINDOW *win = newwin(50, 60, 2, 100);
    
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    char input[30];
    int i = 1;
    int key = 0; 
    while(key != 'q'){
        wmove(win, i,1);
        i++;
        echo();
        wgetstr(win,input, 30);
        mvwprintw(win,i, 1, "Vous avez entré : %s", input);
        wrefresh(win);
        i++;
        key = getch();
    }
    
    


    
    




    
    getch();
    endwin();

    


}

int main(){
    zone();

}
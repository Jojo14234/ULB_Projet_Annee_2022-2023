#include <stdlib.h>
#include <ncurses.h>
#include <vector>

#include "common.h"




using namespace std;

void removeOldMessages(WINDOW *win, int max_messages) {
    int num_lines = getmaxy(win);
    int num_messages = num_lines -1;
    if(num_messages > max_messages) {
        int num_lines_to_remove = num_messages - max_messages;
        for (int i=0; i < num_lines_to_remove; i++) {
            wmove(win, i, 1);
            wdeleteln(win);
        }
        wrefresh(win);
    }
}

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
        wgetstr(win, input);
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
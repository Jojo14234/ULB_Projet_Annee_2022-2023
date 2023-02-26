
#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <unistd.h>

#include "common.h"



string choice(){
    WINDOW* menuwin = newwin(6,30,30,5);
    box(menuwin,0,0);
    wrefresh(menuwin);
    
    keypad(menuwin,true);
    string choices[3] = {"Finir du tour", "Placer des bâtiments","Négocier"};
    int choice;
    int highlight = 0;
    
    while(1){
        for(int i = 0; i <3; i++){
            if(i==highlight){
                wattron(menuwin, A_REVERSE);}
            mvwprintw(menuwin, i+1,1,choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
            
        }
        choice = wgetch(menuwin);
        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                break;
            default:
                break;
        }
        if (choice == 10)
            break;
    }

    
    endwin();

    return choices[highlight];



}


int main(){
    initscr();
    noecho();
    curs_set(0);
    WINDOW* borderwin;
    WINDOW* win;
    win = newwin(10,80,10,10);
    
    borderwin = newwin(12,82,9,9);
    box(borderwin,0,0);
    wrefresh(borderwin);
    vector<char*> a {"le j2 va sur jaune2","jaune2 est possédé par j3","j2 doit 300e à j3","j2 perd 300e","j3 reçoit 300e",
                "j2 est dégouté", "c la hess", "j2 pense à mettre fin à sa vie", "j2 hésite", "que doit faire j2","aider le",
                "voici les actions disponibles" };
    //box(borderwin,0,0);
    //wrefresh(borderwin);
    scrollok(win,true);
    int counter = 0;
    bool key = true;
    while(key == true){
        wprintw(win,"%s\n",a[counter]);
        sleep(1);
        wrefresh(win);
       
        counter++;
        if (counter == a.size()){
            key = false;
        }
        
    }
    string res = choice();
    wprintw(win,"j2 a décidé de ");
    wprintw(win,"%s\n",res.c_str());
    wrefresh(win);

    
    
    wgetch(win);
    endwin();  

}
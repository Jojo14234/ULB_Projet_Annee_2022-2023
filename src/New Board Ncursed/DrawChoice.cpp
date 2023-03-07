#include "DrawChoice.hpp"

DrawChoice::DrawChoice(int n_choice,vector<string> choices):n_choice{n_choice}, choices{choices}{
    choicewin = newwin(choice_size.y,choice_size.x,choice_pos.y,choice_pos.x);
    box(choicewin,0,0);
    wrefresh(choicewin);
    keypad(choicewin,true);

    while(1){
        for(int i = 0; i < n_choice; i++){
            if(i==highlight){
                wattron(choicewin, A_REVERSE);}
            mvwprintw(choicewin, i+1,1,choices[i].c_str());
            wattroff(choicewin, A_REVERSE);}

        choice = wgetch(choicewin);
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
}


//method to get the choice chosen by user
string DrawChoice::getChoice(){
    return choices[highlight];
}

//delete choice window, use this method after user select choice
void DrawChoice::delChoice(){
    wclear(choicewin);  // Efface le contenu de la fenêtre
    wrefresh(choicewin);  // Rafraîchit la fenêtre pour effacer son contenu
    delwin(choicewin);
}
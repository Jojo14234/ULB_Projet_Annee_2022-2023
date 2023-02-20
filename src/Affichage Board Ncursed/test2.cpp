#include <ncurses.h>


void test(){
    WINDOW* a;
    a = newwin( 10, 10 , 50,50);

    wborder(a, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(a,1,1,"gg");

}

int main() {
    // Initialisation de la librairie ncurses
    initscr();

    // Désactivation de l'affichage des caractères saisis
    noecho();

    // Activation du curseur
    curs_set(1);

    // Détermination de la taille de la fenêtre
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calcul de la position de départ de la zone de texte centrée
    int text_start_x = (width - 30) / 2;
    int text_start_y = (height - 3) / 2;

    // Boucle principale du programme
    char input[30];
    int key = 0;
    while(key != 'q'){
        // Affichage d'un cadre autour de la zone de texte centrée
      
        for(int i = text_start_y - 1; i <= text_start_y + 1; i++) {
            move(i, text_start_x - 1);
            for(int j = 0; j < 32; j++) {
                addch(' ');
            }
        }
       


        // Affichage du texte dans la zone centrée
        mvprintw(text_start_y, text_start_x, "Entrez du texte :");

        // Saisie du texte
        echo();
        getnstr(input, 30);

        if (input == "gg"){
            test();
            refresh();}
        // Affichage du texte saisi
        mvprintw(text_start_y + 1, text_start_x, "Vous avez entré : %s", input);
        refresh();
        // Attente de l'appui sur une touche pour effacer le texte saisi
        getch();

        // Nettoyage de la zone de texte
        for(int i = text_start_y; i <= text_start_y + 1; i++) {
            move(i, text_start_x);
            for(int j = 0; j < 30; j++) {
                addch(' ');
            }
        }

        // Attente de l'appui sur une touche pour continuer ou quitter le programme
        
        key = getch();

       
    }

    // Nettoyage de la fenêtre et fermeture de la librairie ncurses
    clear();
    endwin();

    return 0;
}
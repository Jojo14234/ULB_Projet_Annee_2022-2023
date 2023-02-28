#include <ncurses.h>
#include <stdlib.h>
#include <vector>

// position de la souris

using namespace std;

int main() {
    // Initialiser ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Afficher un message
    printw("Cliquez sur n'importe quelle position de la fenêtre pour obtenir sa position...\n");
    refresh();

    // Attendre un clic de souris
    MEVENT event;
    while (true) {
        int ch = getch();
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                // Afficher la position de la souris
                clear();
                printw("Clic de souris détecté à la position (%d,%d) !\n", event.x, event.y);
                refresh();
            }
        }
    }

    // Terminer ncurses
    endwin();

    return 0;
}
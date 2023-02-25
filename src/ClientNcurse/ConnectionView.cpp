#include "ConnectionView.hpp"

ConnectionView::ConnectionView(int height, int width, int starty, int startx) : AbstractView(height, width, starty, startx) {}

ConnectionView::~ConnectionView() {
    clear();
}

void ConnectionView::loginUser() {
    // Username
    clear();
    write("Connexion", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Nom d'utilisateur : ", (LINES-1)/5, (COLS-1)/3);

    char username_buffer[lenght_username]; // initialisation à zéro pour éviter les erreurs
    int username_len = 0;
    curs_set(0);
    while (true) {
        int c = getch();
        if (c == '\n' || c == '\r' ) break;
        else if (c == KEY_BACKSPACE || c == KEY_DC || c == 127) {
            if (username_len > 0) {
                mvaddch((LINES-1)/5, (COLS-1)/3 + 20 + username_len - 1, ' ');
                username_len--;
                username_buffer[username_len] = 0;
            }
        }
        else if (username_len < 31) {
            mvaddch((LINES-1)/5, (COLS-1)/3 + 20 + username_len, c);
            username_len++;
            username_buffer[username_len-1] = c;
        }
    }
    username = username_buffer;

    clearBox((LINES-1)/8, 1, LINES-2, COLS-2);
    write("Connexion", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Mot de passe : ", (LINES-1)/5, (COLS-1)/3);

    char password_buffer[lenght_password];
    int password_len = 0;
    curs_set(0);
    while (true) {
        int c = getch();
        if (c == '\n' || c == '\r') break;
        else if (c == KEY_BACKSPACE || c == KEY_DC || c == 127) {
            if (password_len > 0) {
                mvaddch((LINES-1)/5, (COLS-1)/3 + 15 + password_len - 1, ' ');
                password_len--;
                password_buffer[password_len] = 0;
            }
        }
        else if (password_len < 31) {
            mvaddch((LINES-1)/5, (COLS-1)/3 + 15 + password_len, '*');
            password_len++;
            password_buffer[password_len-1] = c;
        }
    }
    password = password_buffer;
}


void ConnectionView::registerUser() {
        // Username
    clear();
    write("S'enregistrer", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Nom d'utilisateur : ", (LINES-1)/5, (COLS-1)/3);

    char username_buffer[lenght_username]; // initialisation à zéro pour éviter les erreurs
    int username_len = 0;
    curs_set(0);
    while (true) {
        int c = getch();
        if (c == '\n' || c == '\r' ) break;
        else if (c == KEY_BACKSPACE || c == KEY_DC || c == 127) {
            if (username_len > 0) {
                mvaddch((LINES-1)/5, (COLS-1)/3 + 20 + username_len - 1, ' ');
                username_len--;
                username_buffer[username_len] = 0;
            }
        }
        else if (username_len < 31) {
            mvaddch((LINES-1)/5, (COLS-1)/3 + 20 + username_len, c);
            username_len++;
            username_buffer[username_len-1] = c;
        }
    }
    username = username_buffer;

    clearBox((LINES-1)/8, 1, LINES-2, COLS-2);
    write("S'enregistrer", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Mot de passe : ", (LINES-1)/5, (COLS-1)/3);

    char password_buffer[lenght_password];
    int password_len = 0;
    curs_set(0);
    while (true) {
        int c = getch();
        if (c == '\n' || c == '\r') break;
        else if (c == KEY_BACKSPACE || c == KEY_DC || c == 127) {
            if (password_len > 0) {
                mvaddch((LINES-1)/5, (COLS-1)/3 + 15 + password_len - 1, ' ');
                password_len--;
                password_buffer[password_len] = 0;
            }
        }
        else if (password_len < 31) {
            mvaddch((LINES-1)/5, (COLS-1)/3 + 15 + password_len, '*');
            password_len++;
            password_buffer[password_len-1] = c;
        }
    }
    password = password_buffer;
}
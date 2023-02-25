#include "Connection.hpp"

Connection::Connection(int height, int width, int starty, int startx) : Window{height, width, starty, startx} {};


/*void Connection::login() {
    // Username
    clear();
    createBox("CAPITALI$T");
    write("Connexion", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Nom d'utilisateur : ", (LINES-1)/5, (COLS-1)/3);

    
    char username_buffer[64];
    curs_set(1);
    for (int i = 0; i < 64; i++) {
        int c = getch();
        if (c == '\n' || c == '\r') break;
        else {
            username_buffer[i] = c;
            mvaddch((LINES-1)/5, (COLS-1)/3 + 11 + i, c);
        }
    }
    username = username_buffer;
    

    clearBox(8, 1, LINES-2, COLS-2);
    write("Connexion", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Mot de passe : ", (LINES-1)/5, (COLS-1)/3);
    
    char password_buffer[64];
    curs_set(0);
    for (int i = 0; i < 64; i++) {
        int c = getch();
        if (c == '\n' || c == '\r') break;
        else {
            password_buffer[i] = c;
            mvaddch((LINES-1)/5, (COLS-1)/3 + 11 + i, '*');
        }
    }
    password = password_buffer;
}*/


void Connection::login() {
    // Username
    clear();
    createBox("CAPITALI$T");
    write("Connexion", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Nom d'utilisateur : ", (LINES-1)/5, (COLS-1)/3);

    char username_buffer[32]; // initialisation à zéro pour éviter les erreurs
    int username_len = 0;
    curs_set(1);
    while (true) {
        int c = getch();
        if (c == '\n' || c == '\r') break;
        else if (c == KEY_BACKSPACE || c == KEY_DC || c == 127) {
            if (username_len > 0) {
                mvaddch((LINES-1)/5, (COLS-1)/3 + 20 + username_len - 1, ' ');
                username_len--;
                username_buffer[username_len] = 0;
            }
        }
        else if (username_len < 63) {
            mvaddch((LINES-1)/5, (COLS-1)/3 + 20 + username_len, c);
            username_len++;
            username_buffer[username_len-1] = c;
        }
    }
    username = username_buffer;
    cout << username << endl;

    clearBox(8, 1, LINES-2, COLS-2);
    write("Connexion", (LINES-1)/8, (COLS-1)/2 - 4);
    write("Mot de passe : ", (LINES-1)/5, (COLS-1)/3);

    char password_buffer[32]; 
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
        else if (password_len < 63) {
            mvaddch((LINES-1)/5, (COLS-1)/3 + 15 + password_len, '*');
            password_len++;
            password_buffer[password_len-1] = c;
        }
    }
    password = password_buffer;
    cout << password << endl;
}
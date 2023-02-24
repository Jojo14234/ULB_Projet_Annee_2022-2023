#include "Connection.hpp"

Connection::Connection(int height, int width, int starty, int startx, string username, string password) : Window{height, width, starty, startx}, username{username}, password{password} {};


void Connection::login() {
    move(1, 1);
    write("Username: ", 1, 1);

    curs_set(1);
    char username_buffer[64];
    getnstr(username_buffer, 64);
    username = username_buffer;
    

    move(1, 1);
    write("Password : ", 1, 1);

    char password_buffer[64];
    curs_set(0);
    for (int i = 0; i < 64; i++) {
        int c = getch();
        if (c == '\n' || c == '\r') break;
        else {
            password_buffer[i] = c;
            mvaddch(2, i + 12, '*');
        }
    }
    password = password_buffer;
}
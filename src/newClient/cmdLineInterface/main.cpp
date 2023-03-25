//
// Created by Rémy Ryckeboer on 25/03/2023.
//
#include "MainCliWindow.hpp.hpp"

int main() {
    initscr();	// Start curses mode
    MainCliWindow win;	// Create a window
    win.mainLoop();	// Start the main loop
    return 0;
}
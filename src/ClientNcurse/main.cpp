#include "MainWindow.hpp"

int main() {
    initscr();	// Start curses mode
	MainWindow win;	// Create a window
	win.loop();	// Start the main loop
	return 0;
}

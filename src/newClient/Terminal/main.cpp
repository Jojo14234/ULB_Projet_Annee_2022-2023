#include "MainTerminalWindow.hpp"

int main() {
	initscr();	// Start curses mode
	MainTerminalWindow win;	// Create a window
	win.mainLoop();	// Start the main loop
	return 0;
}
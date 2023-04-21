#include "MainCUIWindow.hpp"

int main() {
	initscr();	// Start curses mode
	MainCUIWindow win;	// Create a window
	win.mainLoop();	// Start the main loop
	return 0;
}
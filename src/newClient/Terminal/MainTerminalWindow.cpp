#include <ncurses.h>

#include "MainTerminalWindow.hpp"


// Private

void MainTerminalWindow::initAttributes() {
	// TODO - MainController and MainView
}

void MainTerminalWindow::draw() {
	this->win.draw();
	this->view.draw(state);
	refresh();
}


// Public

MainTerminalWindow::MainTerminalWindow() {
	cbreak();	// Line buffering disabled, Pass on everything to me
	noecho();	// Don't echo() while we do getch
	keypad(stdscr, TRUE);	// I need that nifty F
	mousemask(ALL_MOUSE_EVENTS, NULL);	// To get all mouse events
	refresh();	// Print it on to the real screen
	this->draw();
	this->controller.move(state);
}

MainTerminalWindow::~MainTerminalWindow() {
	endwin();	// End curses mode
}

void MainTerminalWindow::mainLoop() {
	int event;
	while ( (event=getch()) ) {
		if ( event == 27 ) break;	// ESC
		this->controller.handleInput(state, event);
		this->draw();
		this->controller.move(state);
	}
}

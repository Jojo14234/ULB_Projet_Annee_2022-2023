#ifndef _MAIN_WINDOW_HPP
#define _MAIN_WINDOW_HPP

#include <ncurses.h>

#include "Client.hpp"
#include "Controller/MainController.hpp"
#include "View/MainView.hpp"
#include "utils.hpp"


class MainWindow {
	
	Client model{};
	MainController controller{&model};
	MainView view{&model};
	
	// Initial state
	STATE state=STATE::CONNECTION;

public: 

	MainWindow() {
		initscr();	// Start curses mode
		cbreak();	// Line buffering disabled, Pass on everything to me
		noecho();	// Don't echo() while we do getch
		keypad(stdscr, TRUE);	// I need that nifty F
		view.draw(state);
	}

	~MainWindow() {
		endwin();	// End curses mode
	}

	void loop() {
		int ch;
		while ( (ch = getch()) ) {
			if ( ch == 27 ) break;	// ESC
			controller.handleInput(state, ch);
			view.draw(state);
		}
	}

};

#endif

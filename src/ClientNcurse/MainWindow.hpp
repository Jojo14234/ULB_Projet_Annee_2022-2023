#ifndef _MAIN_WINDOW_HPP
#define _MAIN_WINDOW_HPP

#include <iostream>
#include <ncurses.h>

#include "View/Object/Window.hpp"
#include "Client.hpp"
#include "Controller/MainController.hpp"
#include "View/MainView.hpp"
#include "utils.hpp"


class MainWindow {

	Window window{ObjectInfo{LINES/4, COLS/4, LINES/2, COLS/2}, "CAPITALI$T"};

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
		refresh();	// Print it on to the real screen
		this->draw();
	}

	~MainWindow() {
		endwin();	// End curses mode
	}

	void draw() {
		window.draw();
		//view.draw(state);
		refresh();
	}

	void loop() {
		int ch;
		while ( (ch=getch()) ) {
			if ( ch == 27 ) break;	// ESC
			//controller.handleInput(state, ch);
			this->draw();
		}
	}

};

#endif

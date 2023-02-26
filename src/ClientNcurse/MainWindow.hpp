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

	Window win{ObjectInfo{LINES, COLS, 0, 0}, "CAPITALI$T"};

	Client model{};
	MainView view{&model};
	MainController controller{&model, &view};

	// Initial state
	STATE state=STATE::CONNECTION;

public: 

	MainWindow() {
		cbreak();	// Line buffering disabled, Pass on everything to me
		noecho();	// Don't echo() while we do getch
		keypad(stdscr, TRUE);	// I need that nifty F
		mousemask(ALL_MOUSE_EVENTS, NULL);	// To get all mouse events
		refresh();	// Print it on to the real screen
		this->draw();
		this->controller.move(state);
	}

	~MainWindow() {
		endwin();	// End curses mode
	}

	void draw() {
		this->win.draw();
		this->view.draw(state);
		refresh();
	}

	void loop() {
		int ch;
		while ( (ch=getch()) ) {
			if ( ch == 27 ) break;	// ESC
			this->controller.handleInput(state, ch);
			this->draw();
			this->controller.move(state);
		}
	}

};

#endif

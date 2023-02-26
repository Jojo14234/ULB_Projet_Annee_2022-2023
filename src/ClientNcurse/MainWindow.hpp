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

	Window window{ObjectInfo{10, 10, 10, 10}, "CAPITALI$T"};

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
	}

	~MainWindow() {
		endwin();	// End curses mode
	}

	void draw() {
		window.draw();
		view.draw(state);
	}

	void loop() {
		int ch;
		while (true) {
			this->draw();
			ch = getch();
			std::cout << "Key pressed: " << ch << std::endl;	// DEBUG
			if ( ch == 27 ) break;	// ESC
			controller.handleInput(state, ch);
		}
	}

};

#endif

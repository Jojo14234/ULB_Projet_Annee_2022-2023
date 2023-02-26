#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <iostream>
#include <ncurses.h>
#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class Window : public Box {

	std::string title;

public:

	Window(ObjectInfo info, std::string title): Box(info), title(title) {}

	WINDOW* getWin() { return win; }

	void draw() {
		Box::draw();
		std::cout << "Drawing window" << std::endl;	// DEBUG
		mvwprintw(win, (LINES-1)/12, (COLS-3)/2, title.c_str());
		this->refresh();
	}

};

#endif

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

	Window(ObjectInfo info, std::string title): AbstractViewObject(info), Box(info), title(title) {}

	void draw() {
		Box::draw();
		mvwprintw(this->win, 1, (COLS - this->title.length())/2, this->title.c_str());
		this->refresh();
	}

};

#endif

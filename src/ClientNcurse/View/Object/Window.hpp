#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <ncurses.h>
#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class Window : public Box {

	std::string title;

public:

	Window(ObjectInfo info, std::string title): Box(info), title(title) {}

	void draw() {
		Box::draw();
		mvwprintw(win, 0, 1, title.c_str());
		this->refresh();
	}

};

#endif

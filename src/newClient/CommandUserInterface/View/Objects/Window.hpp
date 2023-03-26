/**
 * Project Untitled
 */

#pragma once

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
		if ( !this->isVisible() ) return;
		Box::draw();
		mvwprintw(this->win, 1, (COLS - this->title.length())/2, "%s", this->title.c_str());
		this->refresh();
	}

};
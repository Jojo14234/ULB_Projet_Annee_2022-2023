#ifndef _TEXT_BOX_HPP
#define _TEXT_BOX_HPP

#include <ncurses.h>
#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class TextBox : public virtual Box {

	std::string text;

public:

    TextBox(ObjectInfo info, std::string text) : Box(info), text(text) {
        win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
		box(win, 0, 0);
		this->refresh();
	}

	virtual void draw() override {
		Box::draw();
		mvwprintw(win, 1, 1, text.c_str());
		this->refresh();
	}

};

#endif

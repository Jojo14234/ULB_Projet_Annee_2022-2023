#ifndef _TEXT_BOX_HPP
#define _TEXT_BOX_HPP

#include <ncurses.h>
#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class TextBox : public virtual Box {

	std::string text;

	int getCenteredPos() { return (info.getWidth() - text.length()) / 2; }

public:

    TextBox(ObjectInfo info, std::string text) : Box(info), text(text) {
        win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
	}

	virtual void draw() override {
		Box::draw();
		mvwprintw(win, 1, this->getCenteredPos(), text.c_str());
		this->refresh();
	}

};

#endif

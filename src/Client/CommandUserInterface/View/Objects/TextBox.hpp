/**
 * Project Untitled
 */

#pragma once

#include <ncurses.h>
#include <string>

#include "Box.hpp"
#include "Text.hpp"
#include "AbstractViewObject.hpp"
#include "ObjectInfo.hpp"


class TextBox : public virtual Box, public virtual Text {

	int getCenteredPos() { return (info.getWidth() - texts[0].length()) / 2; }

public:

    TextBox(ObjectInfo info, std::initializer_list<std::string> text, bool centered=true) : AbstractViewObject(info), Box(info), Text(info, text, centered) {}

	virtual void draw() override {
		Box::draw();
		Text::draw();
	}

};
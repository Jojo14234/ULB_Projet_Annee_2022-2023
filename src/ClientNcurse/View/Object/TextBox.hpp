#ifndef _TEXT_BOX_HPP
#define _TEXT_BOX_HPP

#include <ncurses.h>
#include <string>

#include "Box.hpp"
#include "Text.hpp"
#include "AbstractViewObject.hpp"
#include "ObjectInfo.hpp"


class TextBox : public virtual Box, public Text {

	int getCenteredPos() { return (info.getWidth() - texts[0].length()) / 2; }

public:

    TextBox(ObjectInfo info, std::string text) : AbstractViewObject(info), Box(info), Text(info, {text}) {}

	virtual void draw() override {
		Box::draw();
		Text::draw();
	}

};

#endif

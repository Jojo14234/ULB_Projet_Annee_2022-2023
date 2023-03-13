/**
 * Project Untitled
 */

#pragma once

#include "InputBox.hpp"

class HiddenInputBox : public InputBox {

public:
	
	explicit HiddenInputBox(ObjectInfo info) : AbstractViewObject(info), Box(info), InputBox(info) {}

	void draw() override {
		if ( !this->isVisible() ) return;
		this->clear();
		Box::draw();
		mvwprintw(win, 1, this->getTextPos(), "%s", std::string(text.length(), '*').c_str());
		this->refresh();
	}

};

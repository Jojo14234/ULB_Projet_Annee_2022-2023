#ifndef _HIDDEN_INPUT_BOX_HPP
#define _HIDDEN_INPUT_BOX_HPP

#include "InputBox.hpp"

class HiddenInputBox : public InputBox {

public:
	
	explicit HiddenInputBox(ObjectInfo info) : AbstractViewObject(info), Box(info), InputBox(info) {}

	void draw() override {
		if ( !this->isVisible() ) return;
		Box::draw();
		mvwprintw(win, 1, this->getTextPos(), "%s", std::string(text.length(), '*').c_str());
		this->refresh();
	}

};

#endif

#ifndef _INPUT_BUTTON_BOX_HPP
#define _INPUT_BUTTON_BOX_HPP

#include "InputBox.hpp"
#include "Button.hpp"


class InputButtonBox : public InputBox, public Button {

public:
	
	explicit InputButtonBox(ObjectInfo info) : AbstractViewObject(info), Box(info), InputBox(info), Button(info) {}

	void draw() override {
		if ( !this->isVisible() ) return;
		InputBox::draw();
	}

};

#endif

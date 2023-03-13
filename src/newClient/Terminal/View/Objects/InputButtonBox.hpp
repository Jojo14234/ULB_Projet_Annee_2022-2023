/**
 * Project Untitled
 */

#pragma once

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
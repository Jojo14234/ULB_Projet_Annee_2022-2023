#ifndef _INT_INPUT_BUTTON_BOX_HPP
#define _INT_INPUT_BUTTON_BOX_HPP

#include "InputButtonBox.hpp"


class IntInputButtonBox : public InputButtonBox {

protected:

	int value=0;

	virtual bool inputChecker(char c) override {
		if (this->text.length() >= 4) return false;
		return isdigit(c);
	}

public:
	
	explicit IntInputButtonBox(ObjectInfo info) : AbstractViewObject(info), Box(info), InputButtonBox(info) {}

	void draw() override {
		if ( !this->isVisible() ) return;
		InputBox::draw();
	}

	int getValue() { return std::stoi(this->text); }

};

#endif

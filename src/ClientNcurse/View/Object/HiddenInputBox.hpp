#ifndef _HIDDEN_INPUT_BOX_HPP
#define _HIDDEN_INPUT_BOX_HPP

#include "InputBox.hpp"

class HiddenInputBox : public InputBox {

public:
	
	using InputBox::InputBox;

	void draw() override {
		// dessiner la boîte parent
		Box::draw();
		// dessiner le texte
		mvwprintw(win, 1, this->getTextPos(), "%s", std::string(text.length(), '*').c_str());
		this->refresh();
	}

};

#endif

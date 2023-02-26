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
		mvwprintw(win, info.getY()+1, info.getX()+1, "%s", std::string(text.length(), '*').c_str());
		this->refresh();
	}

};

#endif

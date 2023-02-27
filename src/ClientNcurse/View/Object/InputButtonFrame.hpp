#ifndef _INPUT_BUTTON_FRAME_HPP
#define _INPUT_BUTTON_FRAME_HPP

#include "InputButtonBox.hpp"
#include "Text.hpp"


class InputButtonFrame : public InputButtonBox, public Text {

public:
	
	explicit InputButtonFrame(ObjectInfo info) : AbstractViewObject(info), Box(info), InputButtonBox(info), Text(info, {}, false)  {}

	void draw() override {
		this->clear();
		if ( !this->isVisible() ) return;
		Box::draw();
		this->texts.push_back(this->getText());
		Text::draw();
		this->texts.pop_back();
	}

	void addInput() { this->texts.push_back(this->getText()); this->resetInput();  }

	void addText(const std::string &text) { this->texts.push_back(text); }

	void move() override {
		wmove(win, this->texts.size()+1, this->getText().length()+1);
		this->refresh();
	}

};

#endif
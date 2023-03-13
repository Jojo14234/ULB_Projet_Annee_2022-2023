/**
 * Project Untitled
 */

#pragma once

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

	std::string getInput() { return this->texts.back(); }

	void addText(const std::string &text) {
		this->texts.push_back("");
		for (auto c : text) {
			if ( static_cast<int>(this->texts.back().length()) >= this->info.getWidth()-2 ) {
				this->texts.push_back("");
			}
			if (c == '\n') { this->texts.push_back(""); }
			else { this->texts.back() += c; }
		} if (this->texts.back() == "") { this->texts.pop_back(); }
	}

	void move() override {
		wmove(win, this->texts.size()+1, this->getText().length()+1);
		this->refresh();
	}

};
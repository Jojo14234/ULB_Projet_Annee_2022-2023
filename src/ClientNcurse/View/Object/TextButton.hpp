#ifndef _CLIENT_TEXT_BUTTON_HPP_
#define _CLIENT_TEXT_BUTTON_HPP_

#include <string>

#include "TextBox.hpp"
#include "Button.hpp"
#include "ObjectInfo.hpp"


class TextButton : public TextBox, public Button {

public:

	TextButton(ObjectInfo info, std::string text) : AbstractViewObject(info), Box(info), Button(info), TextBox(info, text) {}

	void draw() override { TextBox::draw(); }

};

#endif
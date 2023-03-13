/**
 * Project Untitled
 */

#pragma once

#include <string>

#include "TextBox.hpp"
#include "Button.hpp"
#include "ObjectInfo.hpp"


class TextButton : public Button, public TextBox {

public:

	TextButton(ObjectInfo info, std::string text, bool centered=true) : AbstractViewObject(info), Box(info), Text(info, {text}, centered), Button(info), TextBox(info, {text}, centered) {}

	void draw() override { TextBox::draw(); }

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "ObjectInfo.hpp"
#include "AbstractViewObject.hpp"
#include "InputText.hpp"
#include "Box.hpp"


class InputBox : public InputText, public Box {

public:

	explicit InputBox(ObjectInfo<> info, sf::Color box_color=sf::Color::Black, const std::string &font_path=DEFAULT_FONT_PATH, sf::Color text_color=sf::Color::White) :
		AbstractViewObject(info), InputText(info, text_color, font_path), Box(info, box_color) {}

	virtual void draw(sf::RenderWindow &window) const override {
		Box::draw(window);
		InputText::draw(window);
	}

	void setPosition(double x, double y) {
		InputText::setPosition(x, y);
		Box::setPosition(x, y);
	}

};

class IntInputBox: public InputBox {
public:
	using InputBox::InputBox;
	bool checkValidity(char c) const override{
		return isdigit(c) and (this->getString().length()<4);
	}
};
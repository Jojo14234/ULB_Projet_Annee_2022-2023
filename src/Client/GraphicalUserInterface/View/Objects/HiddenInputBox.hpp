/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "ObjectInfo.hpp"
#include "AbstractViewObject.hpp"
#include "HiddenInputText.hpp"
#include "Box.hpp"


class HiddenInputBox : public HiddenInputText, public Box {

public:

	explicit HiddenInputBox(ObjectInfo<> info, sf::Color box_color=sf::Color::Black, const std::string &font_path=DEFAULT_FONT_PATH, sf::Color text_color=sf::Color::White) :
			AbstractViewObject(info), HiddenInputText(info, text_color, font_path), Box(info, box_color) {}

	virtual void draw(sf::RenderWindow &window) const override {
		Box::draw(window);
		HiddenInputText::draw(window);
	}

	void setPosition(double x, double y) override {
		HiddenInputText::setPosition(x, y);
		Box::setPosition(x, y);
	}


};
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

	explicit InputBox(ObjectInfo<> info, sf::Color text_color=sf::Color::Black, const std::string &font_path=DEFAULT_FONT_PATH, sf::Color box_color=sf::Color::Black) :
		AbstractViewObject(info), InputText(info, text_color, font_path), Box(info, box_color) {}

	virtual void draw(sf::RenderWindow &window) const override {
		Box::draw(window);
		InputText::draw(window);
	}

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "AbstractViewObject.hpp"
#include "../AssetsPath.hpp"


class Text : public virtual AbstractViewObject {
protected:

	sf::Text text;
	sf::Font font;

public:

	Text(ObjectInfo<> info, const std::string &text, sf::Color color=sf::Color::Black, const std::string &font_path=DEFAULT_FONT_PATH) : AbstractViewObject(info) {
		if (!font.loadFromFile(font_path)) {
			throw std::runtime_error("Font not found");
		}
		this->text.setFont(font);
		this->text.setString(text);
		this->text.setCharacterSize(info.getHeight());
		this->text.setFillColor(color);
		this->text.setPosition(info.getX(), info.getY());
	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		window.draw(text);
	}


};
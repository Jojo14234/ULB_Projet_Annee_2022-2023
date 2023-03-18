/**
 * Project Untitled
 */

#pragma once

#include "AbstractViewObject.hpp"


class Text : public virtual AbstractViewObject {

	sf::Text text;

public:

	Text(ObjectInfo<> info, const std::string &text, const std::string &font_path, sf::Color color=sf::Color::Black) : AbstractViewObject(info) {
		/*
		std::cout << font_path << std::endl;
		sf::Font font;
		if (!font.loadFromFile(font_path)) {
			throw std::runtime_error("Font not found");
		}
		*/
		//this->text.setFont(font);
		this->text.setString(text);
		this->text.setCharacterSize(info.getHeight());
		this->text.setFillColor(color);
		this->text.setPosition(info.getX(), info.getY());
	}

	virtual void draw(sf::RenderWindow &window) const override {
		window.draw(text);
	}


};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "InputText.hpp"


class HiddenInputText: public InputText {

	sf::Text hidden_text;

	void updateText() {
		this->hidden_text.setString(std::string(text.getString().getSize(), '*'));
	}

protected:

	void setCursor() override {
		double x = hidden_text.findCharacterPos(cursor_pos).x;
		double y = info.getY();
		cursor.setPosition(x, y);
	}

	void addChar(sf::Uint32 c) override {
		InputText::addChar(c);
		this->updateText();
		this->setCursor();
	}

	void removeChar() override {
		InputText::removeChar();
		this->updateText();
		this->setCursor();
	}

public:

	HiddenInputText(ObjectInfo<> info, sf::Color color=sf::Color::White, const std::string &font_path=DEFAULT_FONT_PATH) :
		AbstractViewObject(info), InputText(info, color, font_path) {
		if (!font.loadFromFile(font_path)) {
			throw std::runtime_error("Font not found");
		}
		this->hidden_text.setFont(font);
		this->hidden_text.setCharacterSize(info.getHeight());
		this->hidden_text.setFillColor(color);
		this->hidden_text.setPosition(info.getX(), info.getY());
	}

	void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		window.draw(hidden_text);
		if (!is_selected) return;
		window.draw(cursor);
	}

	void clear() override {
		InputText::clear();
		this->updateText();
	}

};
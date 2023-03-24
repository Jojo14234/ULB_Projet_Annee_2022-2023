/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "ObjectInfo.hpp"
#include "AbstractViewObject.hpp"
#include "Text.hpp"
#include "Button.hpp"


class InputText: public Text, public Button {

	bool is_selected=false;
	sf::RectangleShape cursor;
	unsigned int max_length = 32;
	unsigned int cursor_pos = 0;
	
protected:

	void setCursor() {
		double x = text.findCharacterPos(cursor_pos).x;
		double y = info.getY();
		cursor.setPosition(x, y);
	}

	void addChar(sf::Uint32 c) {
		if (c >= 128 or c <= 32) { return; }
		if (text.getString().getSize() >= max_length) { return; }
		// Insert the character at the cursor position
		std::string str = text.getString();
		str.insert(cursor_pos, 1, static_cast<char>(c));
		text.setString(str);
		// Update the cursor position and visual cursor
		cursor_pos++;
		this->setCursor();
	}

	void removeChar() {
		if (cursor_pos <= 0) { return; }
		sf::String str = text.getString();
		str.erase(cursor_pos - 1, 1);
		text.setString(str);
		cursor_pos--;
		setCursor();
		sf::Glyph glyph = font.getGlyph(str[cursor_pos], text.getCharacterSize(), false);
		float char_width = glyph.bounds.width;
		cursor.move(-char_width, 0);
	}


public:

	InputText(ObjectInfo<> info, sf::Color color=sf::Color::Black, const std::string &font_path=DEFAULT_FONT_PATH) :
		AbstractViewObject(info), Text(ObjectInfo<>(info.getWidth(), info.getHeight()*0.75, info.getX(), info.getY()), "", color, font_path), Button(info) {
		cursor.setSize(sf::Vector2f(2.f, info.getHeight()));
		cursor.setFillColor(color);
		this->setCursor();
	}

	~InputText()=default;


	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Text::draw(window);
		if (is_selected) window.draw(cursor);
	}

	// Modifiers
	void select() { is_selected=true; }
	void deselect() { is_selected=false; }


	// Checker
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
	virtual bool checkValidity(char c) const {
		return true;
	}
#pragma GCC diagnostic pop

	// Handle
	void handle(sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (this->contains(event.mouseButton.x, event.mouseButton.y)) {
				select();
			} else {
				deselect();
			}
		} else if (event.type == sf::Event::KeyPressed and is_selected) {
			if (event.key.code == sf::Keyboard::BackSpace) {
				removeChar();
			} else if (event.key.code == sf::Keyboard::Enter) {
				deselect();
			}
		} else if (event.type == sf::Event::TextEntered and is_selected and event.text.unicode < 128) {
			char c = static_cast<char>(event.text.unicode);
			if (not checkValidity(c)) return;
			addChar(c);
		}
	}

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "ObjectInfo.hpp"
#include "AbstractViewObject.hpp"
#include "Text.hpp"
#include "Button.hpp"


class InputText: public Text, public Button {

	bool is_selected=false;
	sf::RectangleShape cursor;

public:

	InputText(ObjectInfo<> info, sf::Color color=sf::Color::Black, const std::string &font_path=DEFAULT_FONT_PATH) :
		AbstractViewObject(info), Text(info, "", color, font_path), Button(info) {
		cursor.setSize(sf::Vector2f(2.f, info.getHeight()));
		cursor.setFillColor(color);
		cursor.setPosition(info.getX(), info.getY());
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

	void addChar(char c) {
		std::string str = text.getString();
		str += c;
		text.setString(str);
		cursor.setPosition(cursor.getPosition().x + text.getCharacterSize() / 2.f, cursor.getPosition().y);
	}

	void removeChar() {
		std::string str = text.getString();
		if (str.size() <= 0) return;
		str.pop_back();
		text.setString(str);
		cursor.setPosition(cursor.getPosition().x - text.getCharacterSize() / 2.f, cursor.getPosition().y);
	}

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
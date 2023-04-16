/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"
#include "Box.hpp"
#include "Text.hpp"
#include "ImageButton.hpp"
#include "../configs.hpp"


class FriendBox : public Box {

	Text name;
	ImageButton message;
	ImageButton remove;


public:

	FriendBox(ObjectInfo<> info, const std::string &name) : AbstractViewObject(info), Box(info, TOP_BOX_COLOR) {
		this->name = Text(ObjectInfo<>(0, 5, info.getX()+5, info.getY() + info.getHeight()/2.f - 2.5f), name, sf::Color::Black, DEFAULT_FONT_PATH);
	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		name.draw(window);
		message.draw(window);
		remove.draw(window);
	}

	void move(double new_y) {
		
	}

};

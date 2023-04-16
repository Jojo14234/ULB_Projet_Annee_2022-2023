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

	FriendBox(ObjectInfo<> info, const std::string &name) : AbstractViewObject(info), Box(info, TOP_BOX_COLOR), name(name) {

	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		name.draw(window);
		message.draw(window);
		remove.draw(window);
	}

	void setPosition() {
		
	}

};

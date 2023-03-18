/**
 * Project Untitled
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"
#include "Image.hpp"
#include "Button.hpp"


class ImageButton : public Image, public Button {
public:

	ImageButton(ObjectInfo<> info, const std::string &path) : AbstractViewObject(info), Image(info, path), Button(info) {}

	virtual void draw(sf::RenderWindow &window) const override {
		Image::draw(window);
	}

};
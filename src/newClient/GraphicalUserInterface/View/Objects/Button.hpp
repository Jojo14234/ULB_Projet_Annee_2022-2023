/**
 * Project Untitled
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"


class Button : public virtual AbstractViewObject {
public:

	explicit Button(ObjectInfo<> info) : AbstractViewObject(info) {}

	virtual void draw(sf::RenderWindow &window) const override = 0;

	template<typename T>
	bool contains(T x, T y) const {
		if (isHidden()) return false;
		// if the click pos is inside the button
		return this->info.getX() <= x && x <= this->info.getX() + this->info.getWidth() &&
			this->info.getY() <= y && y <= this->info.getY() + this->info.getHeight();
	}

};
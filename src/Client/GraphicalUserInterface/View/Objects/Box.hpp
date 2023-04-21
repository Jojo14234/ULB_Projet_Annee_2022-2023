/**
 * Project Untitled
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"


class Box : public virtual AbstractViewObject {

	sf::RectangleShape box;

public:

	explicit Box(ObjectInfo<> info, sf::Color color=sf::Color::Black) : AbstractViewObject(info) {
		box.setSize(sf::Vector2f(info.getWidth(), info.getHeight()));
		box.setPosition(info.getX(), info.getY());
		box.setFillColor(color);
	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		window.draw(box);
	}

	void setColor(sf::Color color) { box.setFillColor(color); }

	void setPosition(double x, double y) override {
		AbstractViewObject::setPosition(x, y);
		box.setPosition(x, y);
	}

};
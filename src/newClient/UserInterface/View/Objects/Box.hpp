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

	Box(ObjectInfo<> info, sf::Color color=sf::Color::White) : AbstractViewObject(info) {
		box.setSize(sf::Vector2f(info.getWidth(), info.getHeight()));
		box.setPosition(info.getX(), info.getY());
		box.setFillColor(color);
	}

	virtual void draw(sf::RenderWindow &window) const override {
		window.draw(box);
	}

	void setColor(sf::Color color) { box.setFillColor(color); }


};
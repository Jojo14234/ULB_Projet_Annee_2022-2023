/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"
#include "Box.hpp"


class Border : public Box {

public:

	Border(ObjectInfo<> info, double size, sf::Color color=sf::Color::White) : AbstractViewObject(info),
		Box(ObjectInfo<>(info.getWidth()+2*size, info.getHeight()+2*size, info.getX()-size, info.getY()-size), color) {}

	Border(AbstractViewObject &object, double size, sf::Color color=sf::Color::White) :
		Border(object.getInfo(), size, color) {}

};
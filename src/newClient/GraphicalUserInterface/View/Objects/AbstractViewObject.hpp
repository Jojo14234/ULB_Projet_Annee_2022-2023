/**
 * Project Untitled
 */

#pragma once


#include "ObjectInfo.hpp"


class AbstractViewObject {

	bool visible = true;

protected:

	ObjectInfo<> info;

public:

	AbstractViewObject()=default;

	explicit AbstractViewObject(ObjectInfo<> info) : info(info) {}

	virtual ~AbstractViewObject()=default;

	virtual void draw(sf::RenderWindow &window) const = 0;


	// GETTERS
	ObjectInfo<> getInfo() const { return this->info; }

	bool isVisible() const { return this->visible; }
	bool isHidden() const { return !this->visible; }

	// SETTERS
	void setVisible() { this->visible = true; }
	void setHidden() { this->visible = false; }

	void setInfo(ObjectInfo<> info) { this->info = info; }
	void setSize(double width, double height) { this->info.setSize(width, height); }
	void setPosition(double x, double y) { this->info.setPosition(x, y); }

};
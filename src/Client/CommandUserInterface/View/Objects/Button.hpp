/**
 * Project Untitled
 */

#pragma once

#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class Button : public virtual Box {

public:

	explicit Button(ObjectInfo info) : AbstractViewObject(info), Box(info) {}

	bool isClicked(Position pos) const {
		return info.getX() <= pos.getX() && pos.getX() <= info.getX() + info.getWidth() &&
			info.getY() <= pos.getY() && pos.getY() <= info.getY() + info.getHeight();
	}

};
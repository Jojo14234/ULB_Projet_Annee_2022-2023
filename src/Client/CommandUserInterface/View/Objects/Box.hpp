/**
 * Project Untitled
 */

#pragma once

#include <ncurses.h>

#include "AbstractViewObject.hpp"
#include "ObjectInfo.hpp"


class Box : public virtual AbstractViewObject {

public:

    explicit Box(ObjectInfo info) : AbstractViewObject(info) {}

	virtual void draw() {
		if ( !this->isVisible() ) return;
		box(this->win, 0, 0);
		this->refresh();
	}

};
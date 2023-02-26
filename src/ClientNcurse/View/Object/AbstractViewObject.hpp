#ifndef _ABSTRACT_VIEW_OBJECT_HPP
#define _ABSTRACT_VIEW_OBJECT_HPP

#include "ObjectInfo.hpp"


class AbstractViewObject {

protected:

	ObjectInfo info;

public:

	AbstractViewObject(ObjectInfo info) : info(info) {}
	AbstractViewObject(int height, int width, int y, int x) : info(height, width, y, x) {}

	ObjectInfo getInfo() const { return this->info; }

	virtual void draw() = 0;

};

#endif

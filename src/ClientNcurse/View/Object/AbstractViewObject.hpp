#ifndef _ABSTRACT_VIEW_OBJECT_HPP
#define _ABSTRACT_VIEW_OBJECT_HPP

#include "ObjectInfo.hpp"


class AbstractViewObject {

protected:

	ObjectInfo info;

public:

	AbstractViewObject(ObjectInfo info) : info(info) {}
	AbstractViewObject(int x, int y, int width, int height) : info(x, y, width, height) {}

	ObjectInfo getInfo() const { return info; }

	virtual void draw() = 0;

};

#endif

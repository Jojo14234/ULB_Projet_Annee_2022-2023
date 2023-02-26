#ifndef _CLIENT_BUTTON_HPP_
#define _CLIENT_BUTTON_HPP_

#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class Button : public virtual Box {

public:

	using Box::Box;

	bool isClicked(Position pos) const {
		return info.getX() <= pos.getX() && pos.getX() <= info.getX() + info.getWidth() &&
			info.getY() <= pos.getY() && pos.getY() <= info.getY() + info.getHeight();
	}

};

#endif // _CLIENT_BUTTON_HPP_

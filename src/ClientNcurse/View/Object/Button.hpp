#ifndef _CLIENT_BUTTON_HPP_
#define _CLIENT_BUTTON_HPP_

#include <string>

#include "utils.hpp"
#include "Box.hpp"


class Button : public Box {

	Point pos;
	Point size;

public:

	Button(Point pos, Point size, std::string label): pos(pos), size(size) {}

	bool isClicked(Point point) const {
		return pos.x <= point.x && point.x <= pos.x + size.x &&
			pos.y <= point.y && point.y <= pos.y + size.y;
	}

};

#endif // _CLIENT_BUTTON_HPP_

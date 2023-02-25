#ifndef _CLIENT_BUTTON_HPP_
#define _CLIENT_BUTTON_HPP_

#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class Button : public Box {

	std::string label;

public:

	Button(ObjectInfo info, std::string label): Box(info), label(label) {}

	bool isClicked(Point point) const {
		return pos.x <= point.x && point.x <= pos.x + size.x &&
			pos.y <= point.y && point.y <= pos.y + size.y;
	}

};

#endif // _CLIENT_BUTTON_HPP_

/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"
#include "Text.hpp"
#include "../configs.hpp"
#include "../../configs.hpp"


class Message : public Text {


public:

	explicit Message(ObjectInfo<> info, const std::string &msg, const std::string &sender="moi") : AbstractViewObject(info), Text(info, sender + " :\n" + msg) {

	}

	void move(double new_y) {
		Text::setPosition(getInfo().getX(), getInfo().getY() + new_y);
	}

};
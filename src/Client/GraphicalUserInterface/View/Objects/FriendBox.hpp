/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"
#include "Box.hpp"
#include "Text.hpp"
#include "ImageButton.hpp"
#include "../configs.hpp"
#include "../../configs.hpp"


class FriendBox : public Box {

	Text name;
	ImageButton message;
	ImageButton remove;

public:

	FriendBox(ObjectInfo<> info, const std::string &name) : AbstractViewObject(info), Box(info, TOP_BOX_COLOR) {
		double button_size = WINDOW_WIDTH/30.f;
		double x = info.getX() + info.getWidth() - button_size - 10;
		this->name = Text(ObjectInfo<>(0, button_size/2., info.getX()+5, info.getY() + info.getHeight()/2.f - 2.5f), name, sf::Color::Black, DEFAULT_FONT_PATH); 
		this->message = ImageButton(ObjectInfo<>(button_size, button_size, x, info.getY()+15), MESSAGE_BUTTON_PATH);
		this->remove = ImageButton(ObjectInfo<>(button_size, button_size, x - button_size - 20, info.getY()+15), DELETE_BUTTON_PATH);
	}


	bool operator==(const FriendBox &other) { return this->name.getString() == other.name.getString(); }

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		name.draw(window);
		message.draw(window);
		remove.draw(window);
	}

	void move(double new_y) {
		Box::setPosition(getInfo().getX(), getInfo().getY() + new_y);
		name.setPosition(name.getInfo().getX(), name.getInfo().getY() + new_y);
		message.setPosition(message.getInfo().getX(), message.getInfo().getY() + new_y);
		remove.setPosition(remove.getInfo().getX(), remove.getInfo().getY() + new_y);
	}


	template<typename T>
	bool msgBtnContains(T x, T y) const {
		return this->message.contains(x, y);
	}


	template<typename T>
	bool rmvBtnContains(T x, T y) const {
		return this->remove.contains(x, y);
	}

	std::string getUsername() const { return this->name.getString(); }


};
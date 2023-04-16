/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AbstractViewObject.hpp"
#include "Box.hpp"


template<typename Drawable>
class ScrollBox: public Box {


	std::vector<std::unique_ptr<Drawable>> objects;
	short scroll=0;
	double size;
	const short sep = 5;

	void updateObjects(short int x) {
		for (auto &obj : objects) {
			obj->move(x*size + x*sep);
		}
	}


public:

	ScrollBox(ObjectInfo<> info, double size, sf::Color color=sf::Color(0, 0, 0, 0)) : AbstractViewObject(info), Box(info, color), size(size) {
		
	}


	void addObject(Drawable* obj) {
		this->objects.emplace_back(obj);
	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		for (short i=0; i<5; i++ ) {
			if (this->scroll+i >= this->objects.size()) break; 
			this->objects[this->scroll+i]->draw(window);
		}
	}


	virtual void scrollUp() {
		if (this->scroll >= 5) return;
		this->scroll++; 
		updateObjects(1);
	}

	virtual void scrollDown() {
		if (this->scroll <= 0) return;
		this->scroll--;
		updateObjects(-1);
	}


};
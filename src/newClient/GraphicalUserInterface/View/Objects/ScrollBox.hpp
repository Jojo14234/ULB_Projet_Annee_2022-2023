/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


#include "AbstractViewObject.hpp"


template<typename Drawable>
class ScrollBox: public AbstractViewObject {


	std::vector<std::unique_ptr<Drawable>> objects;
	short scroll=0;
	double size;

	void updateObjects() {

	}


public:

	ScrollBox(ObjectInfo<> info, double size) : AbstractViewObject(info), size(size) {
		
	}


	void addObject(Drawable* obj) {
		this->objects.emplace_back(obj);
	}

	virtual void draw(sf::RenderWindow &window) const override {
		for (short i=0; i<5; i++ ) {
			if (this->scroll+i >= this->objects.size()) break; 
			this->objects[this->scroll+i]->draw(window);
		}
	}


	virtual void scrollUp() {
		if (this->scroll >= 5) return;
		this->scroll++; 
		updateObjects();
	}

	virtual void scrollDown() {
		if (this->scroll <= 0) return;
		this->scroll--;
		updateObjects();
	}


};
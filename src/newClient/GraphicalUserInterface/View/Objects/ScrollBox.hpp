/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>	

#include "AbstractViewObject.hpp"
#include "Box.hpp"
#include "Button.hpp"


template<typename Drawable>
class ScrollBox: public Box, public Button {


	std::vector<std::unique_ptr<Drawable>> objects;
	short scroll=0;
	double size;
	const short sep = 10;
	short max_obj_to_show = 5;

	void updateObjects(short x) {
		for (auto &obj : objects) {
			obj->move(x*(size+sep));
		}
	}


public:

	ScrollBox(ObjectInfo<> info, double size, sf::Color color=sf::Color(0, 0, 0, 0)) : AbstractViewObject(info), Box(info, color), Button(info), size(size) {
		
	}


	void addObject(Drawable* obj) {
		this->objects.emplace_back(obj);
	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		for (short i=0; i<this->max_obj_to_show; i++ ) {
			if (this->scroll+i >= (int)(this->objects.size())) break; 
			this->objects[this->scroll+i]->draw(window);
		}
	}


	virtual void scrollUp() {
		if (this->scroll >= (int)(this->objects.size()-1)) return;
		this->scroll++; 
		updateObjects(-1);
	}

	virtual void scrollDown() {
		if (this->scroll <= 0) return;
		this->scroll--;
		updateObjects(1);
	}

	void setMaxObjToShow(short x) { this->max_obj_to_show = x; }


	void remove(const Drawable& obj) {
		int x = 0;
		for (const auto &object : this->objects) {
			if (obj == (*object)) {
				this->objects.erase(this->objects.begin() + x); break;
			} x++;
		}
	}



	class Iterator {

		std::vector<std::unique_ptr<Drawable>> &objects;
		int idx;

	public:

		Iterator(std::vector<std::unique_ptr<Drawable>> &objects, int idx=0) : objects{objects}, idx{idx} {}

		Drawable &operator*() { return *(this->objects[idx]); }

		Iterator &operator++() { this->idx++; return *this; }
		Iterator &operator--() { this->idx--; return *this; }

		Iterator operator+(int x) const { return Iterator(this->objects, idx + x); }
		Iterator operator-(int x) const { return Iterator(this->objects, idx - x); }

		auto operator<=>(const Iterator &other) const { return this->idx <=> other.idx; }
		bool operator==(const Iterator &other) const { return this->idx == other.idx; }

	};


	Iterator begin() { return Iterator(this->objects, this->scroll); }

	Iterator end() { return Iterator(this->objects, std::min(this->scroll+this->max_obj_to_show+1, (int)this->objects.size())); }


};
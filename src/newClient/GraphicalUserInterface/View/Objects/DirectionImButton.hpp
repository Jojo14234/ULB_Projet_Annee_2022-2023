#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "AbstractViewObject.hpp"
#include "ImageButton.hpp"

#include "observer_struct.hpp"

class DirectionImButton : public ImageButton, public Subject {
	std::string path; //L or R
	int* actual_idx;		//dans selector
	int size;
public:

	DirectionImButton()=default;

	DirectionImButton(ObjectInfo<> info, const std::string &path):AbstractViewObject(info), ImageButton(info,path) {}

	virtual void draw(sf::RenderWindow &window) const override {
		Image::draw(window);
	}

	std::string getPath(){return this->path;};

	void click(){
		int change;
		if (this->path == LEFT_BUTTON_PATH){
			change = -1;	//faire le modulo (en gros, + la taille youpi)
		}
		else {
			change = 1;
		}
		notifyObserver(change);
	}

};
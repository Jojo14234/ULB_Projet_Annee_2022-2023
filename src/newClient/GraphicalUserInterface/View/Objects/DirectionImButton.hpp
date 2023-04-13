#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "AbstractViewObject.hpp"
#include "ImageButton.hpp"


class DirectionImButton : public ImageButton {
	std::string path; //L or R
	int* actual_idx;		//dans selector
	int size;
public:

	DirectionImButton()=default;

	DirectionImButton(ObjectInfo<> info, const std::string &path, int* idx, int size):AbstractViewObject(info), ImageButton(info,path), path{path}, actual_idx{idx}, size{size} {}

	virtual void draw(sf::RenderWindow &window) const override {
		Image::draw(window);
	}

	void click(){
		if (this->path == LEFT_BUTTON_PATH){
			(*(this->actual_idx)--)%size+size;	//faire le modulo (en gros, + la taille youpi)
		}
		else {
			(*(this->actual_idx)++)%size;
		}
	}

};
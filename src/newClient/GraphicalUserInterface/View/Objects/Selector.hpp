#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "AbstractViewObject.hpp"
#include "ImageButton.hpp"
#include "Text.hpp"

#include "../../configs.hpp"
#include "../AssetsPath.hpp"

class DirectionImButton : public ImageButton {
	int* actual_idx;		//dans selector
	std::string path; //L or R
	int size;
public:
	DirectionImButton(ObjectInfo<> info, const std::string &path, int* idx, int size) 
	AbstractViewObject(info), Image(info, path), Button(info), path{path}, actual_idx{idx}, size{size} {}

	virtual void draw(sf::RenderWindow &window) const override {
		Image::draw(window);
	}

	void click(){
		if (this->path == LEFT_BUTTON_PATH){
			(this->actual_idx--)%size+size;	//faire le modulo (en gros, + la taille youpi)
		}
		else {
			this->actual_idx++%size;
		}
	}

}

class Selector : public virtual AbstractViewObject {
	std::vector<std::string> choices;
	DirectionImButton left_button;
	DirectionImButton right_button;
	Text text;
	int actual_idx = 0;

public:
	Selector(ObjectInfo<> info, std::vector<std::string> str_choices): choices{str_choices} {
		this->text = Text{info, choices.at(actual_idx)}; //idx 0

		float button_size = WINDOW_WIDTH/50.f;
		float pos_x = info.getX();
		float pos_y = info.getY() - button_size;

		this->left_button = DirectionImButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_y), LEFT_BUTTON_PATH, this->actual_idx, choices.size()};
		this->right_button = DirectionImButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_x+WINDOW_HEIGHT/10.f, pos_y), RIGHT_BUTTON_PATH, this->actual_idx, choices.size()};
	}

	virtual void draw(sf::RenderWindow &window) const override {
		this->text.setString(choices.at(actual_idx));	//couteux ?
        text.draw(window);
        left_button.draw(window);
        right_button.draw(window);
    }

    DirectionImButton getLButton() {
    	return &left_button;
    }

    DirectionImButton getRButton() {
    	return &right_button;
    }

}


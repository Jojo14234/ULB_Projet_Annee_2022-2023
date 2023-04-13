#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "AbstractViewObject.hpp"
#include "ImageButton.hpp"
#include "Text.hpp"

#include "../../configs.hpp"
#include "../AssetsPath.hpp"

class Selector : public virtual AbstractViewObject {
	std::vector<std::string> choices;
	ImageButton left_button;
	ImageButton right_button;
	Text text;
	actual_idx = 0;

public:
	Selector(ObjectInfo<> info, std::vector<std::string> str_choices): choices{str_choices} {
		this->text = Text{info, choices.at(actual_idx)}; //idx 0

		float button_size = WINDOW_WIDTH/50.f;
		float pos_x = info.getX();
		float pos_y = info.getY() - button_size;

		this->left_button = ImageButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_y)};
		this->right_button = ImageButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_x+WINDOW_HEIGHT/10.f, pos_y)};
	}

	virtual void draw(sf::RenderWindow &window) const override {
        text.draw(window);
        left_button.draw(window);
        right_button.draw(window);
    }

    void clickLeft(){
    	this->actual_idx = (actual_idx--)%choices.size();
    	this->text.setString(choices.at(actual_idx));
    }

    void clickLeft(){
    	this->actual_idx = (actual_idx++)%choices.size();
    	this->text.setString(choices.at(actual_idx));
    }

}
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "AbstractViewObject.hpp"
#include "DirectionImButton.hpp"
#include "Text.hpp"

#include "../../configs.hpp"
#include "../AssetsPath.hpp"


class Selector : public virtual AbstractViewObject {
	std::vector<std::string> choices;
	DirectionImButton left_button;
	DirectionImButton right_button;
	Text text;
	int actual_idx = 0;

public:
	Selector(ObjectInfo<> info, std::vector<std::string> str_choices): AbstractViewObject(info),choices{str_choices} {
		this->text = Text{info, choices.at(actual_idx)}; //idx 0

		float button_size = WINDOW_WIDTH/50.f;
		float pos_x = info.getX();
		float pos_y = info.getY() - button_size;

		this->left_button = DirectionImButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_y), LEFT_BUTTON_PATH, &actual_idx, choices.size()};
		this->right_button = DirectionImButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_y+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH, &actual_idx, choices.size()};
	}

	virtual void draw(sf::RenderWindow &window) const override {
		std::cout<<"in draw selector -";
        text.draw(window);
        std::cout<<"text has been draw -";
        left_button.draw(window);
        std::cout<<"l button has been draw -";
        right_button.draw(window);
        std::cout<<"r button has been draw"<<std::endl;
    }

    DirectionImButton* getLButton() {
    	return &left_button;
    }

    DirectionImButton* getRButton() {
    	return &right_button;
    }

    void changeText(){
    	this->text.setString(choices.at(actual_idx));
    }

};


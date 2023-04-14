#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "AbstractViewObject.hpp"
#include "DirectionImButton.hpp"
#include "Text.hpp"

#include "../../configs.hpp"
#include "../AssetsPath.hpp"

#include "observer_struct.hpp"

class Selector : public AbstractViewObject, public Observer {
	std::vector<std::string> choices;
	std::vector<DirectionImButton*> buttons;
	Text text;
	int actual_idx = 0;
	int choices_size;

public:
	Selector(ObjectInfo<> info, std::vector<std::string> str_choices,std::vector<DirectionImButton*> buttons): AbstractViewObject(info),choices{str_choices}, buttons{buttons} {
		for (auto button:buttons) {
			button->registerObserver(this);
		}

		this->text = Text{info, choices.at(actual_idx)}; //idx 0
		this->choices_size = choices.size();

		/*float button_size = WINDOW_WIDTH/50.f;
		float pos_x = info.getX();
		float pos_y = info.getY() - button_size;

		this->left_button = DirectionImButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_y), LEFT_BUTTON_PATH, &actual_idx, choices.size()};
		this->right_button = DirectionImButton{ObjectInfo<>(button_size, button_size, pos_x-button_size, pos_y+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH, &actual_idx, choices.size()};*/
	}

	~Selector() {
		std::cout<<"boum boum boum"<<std::endl;
		for (auto button:buttons) {
			button->removeObserver(this);
			delete button;
		}
	}

	void update(int change) override {
		this->actual_idx += change % choices_size + choices_size;
		this->changeText();
	}

	virtual void draw(sf::RenderWindow &window) const override {
		std::cout<<"in draw selector -" << std::endl;
        text.draw(window);
        std::cout<<"text has been draw -" << std::endl;
        for (auto button:buttons) {
			button->draw(window);
		}

        //left_button.draw(window);
        std::cout<<"l button has been draw -";
        //right_button.draw(window);
        std::cout<<"r button has been draw"<<std::endl;
    }

    DirectionImButton* getLButton() {
    	return buttons.at(0);
    }

    DirectionImButton* getRButton() {
    	return buttons.at(1);
    }

    void changeText(){
    	this->text.setString(choices.at(actual_idx));
    }

};


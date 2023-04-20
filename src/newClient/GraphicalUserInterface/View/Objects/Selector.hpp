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

	Selector(ObjectInfo<> info) : AbstractViewObject(info) {}

	Selector(ObjectInfo<> info, std::vector<std::string> str_choices,std::vector<DirectionImButton*> buttons): AbstractViewObject(info),choices{str_choices}, buttons{buttons} {
		for (auto button:buttons) {
			button->registerObserver(this);
		}

		this->text = Text{info, choices.at(actual_idx)}; //idx 0
		this->choices_size = choices.size();
	}

	~Selector() {
		for (auto button:buttons) {
			button->removeObserver(this);
			delete button;
		}
	}

	void addChoice(const std::string &choice) {
		this->choices.push_back(choice);
		this->choices_size++;
	}

	void update(int change) override {
		this->actual_idx = (this->actual_idx + change)% choices_size;
		this->changeText();
	}

	virtual void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
        text.draw(window);
        for (auto button:buttons) {
			button->draw(window);
		}
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

    std::string getActualString() {
    	return this->choices.at(this->actual_idx);
    }

};


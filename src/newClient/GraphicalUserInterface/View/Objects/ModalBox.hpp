/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>
#include <vector>
#include <memory>

#include "Box.hpp"
#include "Text.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "InputBox.hpp"

#include "Selector.hpp"

#include "../../configs.hpp"


class ModalBox : public Box {
protected:

	Box background{ObjectInfo<>(WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 0.f), sf::Color(0, 0, 0, 180)};
	std::vector<std::unique_ptr<Text>> texts;
	std::vector<std::unique_ptr<Image>> images;
	std::vector<std::unique_ptr<ImageButton>> buttons;
	std::vector<std::unique_ptr<InputBox>> inputs;

	std::vector<std::unique_ptr<Selector>> selectors;
	//std::vector<std::unique_ptr<DirectionImButton>> dir_buttons;
public:

	explicit ModalBox(ObjectInfo<> info, sf::Color color=sf::Color::Black) : AbstractViewObject(info), Box(info, color) {}

	~ModalBox()=default;

	void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		background.draw(window);
		Box::draw(window);
		for (auto &image : images) image->draw(window);
		for (auto &text : texts) text->draw(window);
		for (auto &button : buttons) button->draw(window);
		for (auto &input : inputs) input->draw(window);
		std::cout<<"draw modal box before selectors"<<std::endl;
		for (auto &selector : selectors) selector->draw(window);
		std::cout<<"draw modal box after selectors"<<std::endl;
	}

	// Setters
	void addText(Text* text) { texts.emplace_back(text); }
	void addImage(Image* image) { images.emplace_back(image); }
	void addButton(ImageButton* button) { buttons.emplace_back(button); }
	void addInput(InputBox* input) { inputs.emplace_back(input); }
	void addSelector(Selector* selector) {
		std::cout<<"in add selector -";
		selectors.emplace_back(selector);
		std::cout<<"selector added -";
/*		dir_buttons.emplace_back(selector->getLButton());	//new ?
		std::cout<<"left button there -";
		dir_buttons.emplace_back(selector->getRButton());
		std::cout<<"right button here -"<<std::endl;*/
	}

	void addTexts(std::initializer_list<Text*> texts) { for (Text* text : texts) this->addText(text); }
	void addImages(std::initializer_list<Image*> images) { for (Image* image : images) this->addImage(image); }
	void addButtons(std::initializer_list<ImageButton*> buttons) { for (ImageButton* button : buttons) this->addButton(button); }
	void addInputs(std::initializer_list<InputBox*> inputs) { for (InputBox* input : inputs) this->addInput(input); }


	// Getters
	Text* getText(int index) { return texts[index].get(); }
	Image* getImage(int index) { return images[index].get(); }
	ImageButton* getButton(int index) { return buttons[index].get(); }
	InputBox* getInput(int index) { return inputs[index].get(); }
	Selector* getSelector(int index) { return selectors[index].get(); }
	//DirectionImButton* getDirButton(int index) { return dir_buttons[index].get(); }

};
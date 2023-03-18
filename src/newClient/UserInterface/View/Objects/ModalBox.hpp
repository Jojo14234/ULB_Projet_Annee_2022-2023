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


class ModalBox : public Box {

	std::vector<std::unique_ptr<Text>> texts;
	std::vector<std::unique_ptr<Image>> images;
	std::vector<std::unique_ptr<ImageButton>> buttons;

public:

	using Box::Box;

	~ModalBox()=default;

	void draw(sf::RenderWindow &window) const override {
		Box::draw(*window);
		for (Image* image : images) image->draw(*window);
		for (Text* text : texts) text->draw(*window);
		for (Button* button : buttons) button->draw(*window);
	}

	// Setters
	void addTexts(std::initializer_list<Text*> texts) { for (Text* text : texts) this->add(text); }
	void addImages(std::initializer_list<Image*> images) { for (Image* image : images) this->add(image); }
	void addButtons(std::initializer_list<ImageButton*> buttons) { for (ImageButton* button : buttons) this->add(button); }

	void addText(Text* text) { texts.emplace_back(text); }
	void addImage(Image* image) { images.emplace_back(image); }
	void addButton(ImageButton* button) { buttons.emplace_back(button); }

	// Getters
	Text* getText(int index) { return texts[index].get(); }
	Image* getImage(int index) { return images[index].get(); }
	ImageButton* getButton(int index) { return buttons[index].get(); }

};
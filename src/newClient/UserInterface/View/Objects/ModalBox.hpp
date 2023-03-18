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
#include "../../configs.hpp"


class ModalBox : public Box {

	Box background{ObjectInfo<>(WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 0.f), sf::Color(0, 0, 0, 180)};
	std::vector<std::unique_ptr<Text>> texts;
	std::vector<std::unique_ptr<Image>> images;
	std::vector<std::unique_ptr<ImageButton>> buttons;

public:

	ModalBox(ObjectInfo<> info, sf::Color color=sf::Color::Black) : AbstractViewObject(info), Box(info, color) {}

	~ModalBox()=default;

	void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		background.draw(window);
		Box::draw(window);
		for (auto &image : images) image->draw(window);
		for (auto &text : texts) text->draw(window);
		for (auto &button : buttons) button->draw(window);
	}

	// Setters
	void addText(Text* text) { texts.emplace_back(text); }
	void addImage(Image* image) { images.emplace_back(image); }
	void addButton(ImageButton* button) { buttons.emplace_back(button); }

	void addTexts(std::initializer_list<Text*> texts) { for (Text* text : texts) this->addText(text); }
	void addImages(std::initializer_list<Image*> images) { for (Image* image : images) this->addImage(image); }
	void addButtons(std::initializer_list<ImageButton*> buttons) { for (ImageButton* button : buttons) this->addButton(button); }


	// Getters
	Text* getText(int index) { return texts[index].get(); }
	Image* getImage(int index) { return images[index].get(); }
	ImageButton* getButton(int index) { return buttons[index].get(); }

};
/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"


class ConnectionUIController; // forward declaration

class ConnectionUIView: public AbstractUIView {

	// Objects

	InputBox username{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_HEIGHT/20.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/8.f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/20.f), sf::Color(255, 255, 255), SERIF_FONT_PATH, sf::Color(100, 0, 100)};
	InputBox password{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_HEIGHT/20.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/8.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/20.f), sf::Color(255, 255, 255), SERIF_FONT_PATH, sf::Color(100, 0, 100)};

	ModalBox modal_box{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), sf::Color(255, 100, 100)};


public:

	explicit ConnectionUIView(sf::RenderWindow* window) : AbstractUIView(window) {
		modal_box.addText(new Text{ObjectInfo<>(0, 80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), "Welcome to the game!"});
		modal_box.setHidden();
	}

	~ConnectionUIView()=default;

	void draw() override {
		username.draw(*window);
		password.draw(*window);
		modal_box.draw(*window);
	}

	void clear();

	friend class ConnectionUIController;

};
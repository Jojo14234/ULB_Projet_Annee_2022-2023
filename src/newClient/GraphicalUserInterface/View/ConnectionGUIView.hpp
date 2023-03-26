/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"


class ConnectionGUIController; // forward declaration

class ConnectionGUIView: public AbstractGUIView {

	// Objects
	Image logo{ObjectInfo<>(788.f, 145.f, WINDOW_WIDTH/2.f - 788.f/2.f, WINDOW_HEIGHT/10.f), LOGO_PATH};
	Box background{ObjectInfo<>(WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 0.f), sf::Color(98, 205, 255)};

	InputBox username{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/15.f), sf::Color(255, 255, 255), SERIF_FONT_PATH, sf::Color(100, 0, 100)};
	InputBox password{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/15.f), sf::Color(255, 255, 255), SERIF_FONT_PATH, sf::Color(100, 0, 100)};

	ModalBox modal_box{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), sf::Color(255, 100, 100)};


public:

	explicit ConnectionGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {
		modal_box.addText(new Text{ObjectInfo<>(0, 80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), "Welcome to the game!"});
		modal_box.setHidden();
	}

	~ConnectionGUIView()=default;

	void draw() override {
		background.draw(*window);
		logo.draw(*window);
		username.draw(*window);
		password.draw(*window);
		modal_box.draw(*window);
	}

	void clear();

	friend class ConnectionGUIController;

};
/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"


class WelcomeUIController; // forward declaration

class WelcomeUIView: public AbstractUIView {

	// Objects
	Image logo{ObjectInfo<>(788.f, 145.f, WINDOW_WIDTH/2.f - 788.f/2.f, WINDOW_HEIGHT/10.f), LOGO_PATH};
	Box background{ObjectInfo<>(WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 0.f), sf::Color(98, 205, 255)};
	ModalBox modal_box{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), sf::Color(255, 100, 100)};

public:

	WelcomeUIView(sf::RenderWindow* window) : AbstractUIView(window) {
		modal_box.addText(new Text{ObjectInfo<>(0, 80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), "Welcome to the game!"});
	}
	
	~WelcomeUIView()=default;

	void draw() override {
		background.draw(*window);
		logo.draw(*window);
		//modal_box.draw(*window);
	}

	friend class WelcomeUIController;

};
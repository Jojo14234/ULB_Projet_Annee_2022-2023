/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"


class WelcomeGUIController; // forward declaration

class WelcomeGUIView: public AbstractGUIView {

	// Objects
	Image logo{ObjectInfo<>(788.f, 145.f, WINDOW_WIDTH/2.f - 788.f/2.f, WINDOW_HEIGHT/10.f), LOGO_PATH};

public:

	explicit WelcomeGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {}
	
	~WelcomeGUIView()=default;

	void draw() override {
		logo.draw(*window);
	}

	friend class WelcomeGUIController;

};
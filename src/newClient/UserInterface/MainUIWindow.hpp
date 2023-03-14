/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../AbstractMainWindow.hpp"
#include "AbstractUI.hpp"
#include "configs.hpp"


class MainUIWindow: public AbstractMainWindow<STATE, sf::Event>, public AbstractUI {

	// attributes
	sf::RenderWindow window;


	void initAttributes() override;

	void draw() override;

public:
	
	MainUIWindow();
	
	~MainUIWindow();
	
	void mainLoop() override;

};
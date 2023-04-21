/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../AbstractMainWindow.hpp"
#include "AbstractGUI.hpp"
#include "configs.hpp"


class MainGUIWindow: public AbstractMainWindow<STATE, sf::Event>, public AbstractGUI {

	// attributes
	sf::RenderWindow window;


	void initAttributes() override;

	void draw() override;

	void clear();

public:
	
	MainGUIWindow();
	
	~MainGUIWindow();
	
	void mainLoop() override;

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "../AbstractMainWindow.hpp"
#include "AbstractUI.hpp"
#include "configs.hpp"


class MainUIWindow: public AbstractMainWindow<STATE, sf::Event>, public AbstractUI {

	// attributes

	void initAttributes() override;

	void draw() override;

public:
	
	using AbstractMainWindow<STATE, sf::Event>::AbstractMainWindow;
	
	~MainUIWindow()=default;
	
	void mainLoop() override;

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "../../Controller/AbstractController.hpp"
#include "../AbstractGUI.hpp"
#include "../configs.hpp"


class AbstractGUIController: public AbstractController<STATE, sf::Event>, public AbstractGUI {

public:
	
	using AbstractController<STATE, sf::Event>::AbstractController;

	virtual ~AbstractGUIController()=default;

	virtual void move() override {}

	virtual void handle(sf::Event event) override = 0;

};
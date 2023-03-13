/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "../../Controller/AbstractController.hpp"
#include "../AbstractUI.hpp"
#include "../configs.hpp"


class AbstractUIController: public AbstractController<STATE, sf::Event>, public AbstractUI {

public:
	
	using AbstractController<STATE, sf::Event>::AbstractController;

	virtual ~AbstractUIController()=default;

	virtual void handle(sf::Event event) override = 0;

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class WelcomeGUIView; // forward declaration

class WelcomeGUIController: public AbstractGUIController {


	WelcomeGUIView* view;

public: 
	
	WelcomeGUIController(Client* model, WelcomeGUIView* view) : AbstractGUIController(model, STATE::WELCOME), view{view} {}

	~WelcomeGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
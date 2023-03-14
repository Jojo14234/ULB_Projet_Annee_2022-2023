/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class WelcomeUIView; // forward declaration

class WelcomeUIController: public AbstractUIController {


	WelcomeUIView* view;

public: 
	
	WelcomeUIController(Client* model, WelcomeUIView* view) : AbstractUIController(model, STATE::WELCOME), view{view} {}

	~WelcomeUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
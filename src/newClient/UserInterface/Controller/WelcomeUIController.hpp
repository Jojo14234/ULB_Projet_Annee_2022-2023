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
	
	WelcomeUIView(Client* model, WelcomeUIView* view) : AbstractUIController(model, STATE::Welcome), view{view} {}

	~WelcomeUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
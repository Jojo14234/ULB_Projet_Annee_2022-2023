/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class MenuUIView; // forward declaration

class MenuUIController: public AbstractUIController {


	MenuUIView* view;

public: 
	
	MenuUIView(Client* model, MenuUIView* view) : AbstractUIController(model, STATE::Menu), view{view} {}

	~MenuUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
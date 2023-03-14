/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class MenuUIView; // forward declaration

class MenuUIController: public AbstractUIController {


	MenuUIView* view;

public: 
	
	MenuUIController(Client* model, MenuUIView* view) : AbstractUIController(model, STATE::MENU), view{view} {}

	~MenuUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
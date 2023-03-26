/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class MenuGUIView; // forward declaration

class MenuGUIController: public AbstractGUIController {


	MenuGUIView* view;

public: 
	
	MenuGUIController(Client* model, MenuGUIView* view) : AbstractGUIController(model, STATE::MENU), view{view} {}

	~MenuGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class ConnectionGUIView; // forward declaration

class ConnectionGUIController: public AbstractGUIController {

	enum CONNECTION_STATE { USERNAME, PASSWORD, DONE };
	CONNECTION_STATE state = USERNAME;

	ConnectionGUIView* view;

public: 
	
	ConnectionGUIController(Client* model, ConnectionGUIView* view) : AbstractGUIController(model, STATE::CONNECTION), view{view} {}

	~ConnectionGUIController()=default;

	void handle(sf::Event event) override;

	void clear();

	// ...

};
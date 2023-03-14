/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class ConnectionUIView; // forward declaration

class ConnectionUIController: public AbstractUIController {

	enum CONNECTION_STATE { USERNAME, PASSWORD, DONE };
	CONNECTION_STATE state = USERNAME;

	ConnectionUIView* view;

public: 
	
	ConnectionUIController(Client* model, ConnectionUIView* view) : AbstractUIController(model, STATE::CONNECTION), view{view} {}

	~ConnectionUIController()=default;

	void handle(sf::Event event) override;

	void clear();

	// ...

};
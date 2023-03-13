/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalController.hpp"
#include "../configs.hpp"


class ConnectionTerminalView; // forward declaration

class ConnectionTerminalController: public AbstractTerminalController {

	enum CONNECTION_STATE = { USERNAME, PASSWORD, DONE };
	CONNECTION_STATE state = USERNAME;

	ConnectionTerminalView* view;

public: 
	
	ConnectionTerminalView(Client* model, ConnectionTerminalView* view) : AbstractTerminalController(model, STATE::CONNECTION), view{view} {}

	~ConnectionTerminalController()=default;

	void handle(int event) override;
	
	void move() override;

	void clear();

};
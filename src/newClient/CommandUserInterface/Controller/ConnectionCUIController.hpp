/**
 * Project Untitled
 */

#pragma once

#include "AbstractCUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class ConnectionCUIView; // forward declaration

class ConnectionCUIController: public AbstractCUIController {

	enum CONNECTION_STATE { USERNAME, PASSWORD, DONE };
	CONNECTION_STATE state = USERNAME;

	ConnectionCUIView* view;

public: 
	
	ConnectionCUIController(Client* model, ConnectionCUIView* view);

	~ConnectionCUIController()=default;

	void handle(int event) override;
	
	void move() override;

	void clear();

};
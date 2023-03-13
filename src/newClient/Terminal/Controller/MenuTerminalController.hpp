/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class MenuTerminalView; // forward declaration

class MenuTerminalController: public AbstractTerminalController {

	enum MENU_STATE { CONSOLE, JOIN, IDLE };
	MENU_STATE state = IDLE;

	MenuTerminalView* view;

public: 
	
	MenuTerminalView(Client* model, MenuTerminalView* view) : AbstractTerminalController(model, STATE::MENU), view{view} {}

	~MenuTerminalController()=default;

	void handle(int event) override;
	
	void move() override;

};
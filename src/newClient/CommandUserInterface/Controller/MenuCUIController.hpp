#pragma once

#include "AbstractCUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class MenuCUIView; // forward declaration

class MenuCUIController: public AbstractCUIController {

	enum MENU_STATE { CONSOLE, JOIN, IDLE };
	MENU_STATE state = IDLE;

	MenuCUIView* view;

public: 
	
	MenuCUIController(Client* model, MenuCUIView* view);

	~MenuCUIController()=default;

	void handle(int event) override;
	
	void move() override;

};
/**
 * Project Untitled
 */

#pragma once

#include "../../Controller/AbstractController.hpp"
#include "../AbstractTerminal.hpp"
#include "../configs.hpp"


class AbstractTerminalController: public AbstractController<STATE, int>, public AbstractTerminal {

public: 
	
	using AbstractController<STATE, int>::AbstractController;

	virtual ~AbstractTerminalController()=default;

	virtual void handle(int event) override = 0;
	
	virtual void move()=0;

};
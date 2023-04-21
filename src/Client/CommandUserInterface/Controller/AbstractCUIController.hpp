/**
 * Project Untitled
 */

#pragma once

#include "../../Controller/AbstractController.hpp"
#include "../AbstractCUI.hpp"
#include "../configs.hpp"


class AbstractCUIController: public AbstractController<STATE, int>, public AbstractCUI {

public: 
	
	using AbstractController<STATE, int>::AbstractController;

	virtual ~AbstractCUIController()=default;

	virtual void handle(int event) override =0;
	
	virtual void move() override =0;

};
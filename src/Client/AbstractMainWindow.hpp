/**
 * Project Untitled
 */

#pragma once

#include "Model/Client.hpp"
#include "View/MainView.hpp"
#include "Controller/MainController.hpp"


template <typename StateType, typename EventType>
class AbstractMainWindow {

protected:

	Client model;
	MainView<StateType> view;
	MainController<StateType, EventType> controller;
	StateType state = static_cast<StateType>(0);

	virtual void initAttributes()=0;

	virtual void draw()=0;

public:

	AbstractMainWindow()=default;
	
	virtual ~AbstractMainWindow()=default;
	
	virtual void mainLoop()=0;

};
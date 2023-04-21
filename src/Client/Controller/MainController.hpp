/**
 * Project Untitled
 */

#pragma once

#include <vector>
#include <initializer_list>

#include "AbstractController.hpp"


template <typename StateType, typename EventType>
class MainController {

	std::vector<AbstractController<StateType, EventType>*> controllers;

	AbstractController<StateType, EventType>* getController(StateType state) {
		return controllers[static_cast<short>(state)];
	}

public:

	MainController()=default;

	~MainController() { for (auto elem : controllers) delete elem; }

	void handle(StateType &state, EventType event) {
		AbstractController<StateType, EventType>* controller = this->getController(state);
		controller->handle(event);
		state = controller->getNewState();
		controller->resetState();
	}

	void move(StateType &state) {
		AbstractController<StateType, EventType>* controller = this->getController(state);
		controller->move();
	}

	void setController(const std::initializer_list<AbstractController<StateType, EventType>*> &list) { this->controllers = list; }

};
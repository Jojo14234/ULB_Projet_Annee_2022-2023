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

	AbstractController* getController(StateType state) {
		return controllers[static_cast<short>(state)];
	}

public:

	MainController()=default;
	MainController(std::initializer_list<AbstractController*> list) : controllers{list} {}

	~MainController() { for (auto elem : controllers) delete elem; }

	void handle(StateType &state, EventType event) {
		AbstractController* controller = this->getController(state);
		controller->handle(event);
		state = controller->getNewState();
	}

};
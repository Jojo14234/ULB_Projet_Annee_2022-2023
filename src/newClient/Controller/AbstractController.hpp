/**
 * Project Untitled
 */

#pragma once

//#include "../Model/Client.hpp"
class Client; // forward declaration

template <typename StateType, typename EventType>
class AbstractController {

	Client* model;
	StateType new_state;

public: 
	
	AbstractController(Client* model, StateType new_state) : model(model), new_state(new_state) {}

	virtual ~AbstractController()=default;
	
	virtual void handle(EventType event)=0;

	virtual void move() {}

	StateType getNewState() { return new_state; }

};
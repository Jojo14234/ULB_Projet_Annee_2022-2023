#pragma once

//#include "../Model/Client.hpp"
class Client; // forward declaration

template <typename StateType, typename EventType>
class AbstractController {

protected:

	Client* model;
	StateType new_state;
	StateType initial_state;

public: 
	
	AbstractController(Client* model, StateType new_state) : model(model), new_state(new_state), initial_state(new_state) {}

	virtual ~AbstractController()=default;
	
	virtual void handle(EventType event)=0;

	virtual void move()=0;

	void resetState() { new_state = initial_state; }

	StateType getNewState() { return new_state; }
};
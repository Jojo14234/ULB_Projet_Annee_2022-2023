#pragma once

//#include "../Model/Client.hpp"
class Client; // forward declaration

template <typename StateType, typename EventType>
class AbstractController {

protected:

	Client* model;
	StateType new_state;

public: 
	
	AbstractController(Client* model, StateType new_state) : model(model), new_state(new_state) {}

	virtual ~AbstractController()=default;
	
	virtual void handle(EventType event)=0;

	virtual void move()=0;

	StateType getNewState() { return this->new_state; }

};
/**
 * Project Untitled
 */

#pragma once


class Client; // forward declaration

template <typename StateType, typename EventType>
class AbstractController {

	Client* model;
	StateType new_state;

public: 
	
	AbstractController(Client* model, StateType new_state) : model(model), state(state) {}

	virtual ~AbstractController()=default;
	
	virtual void handle(EventType event)=0;

};
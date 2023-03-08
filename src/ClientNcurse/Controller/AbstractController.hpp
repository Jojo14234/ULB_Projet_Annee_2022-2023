#ifndef _ABSTRACT_CONTROLLER_HPP
#define _ABSTRACT_CONTROLLER_HPP

#include "../Client.hpp"
#include "../utils.hpp"


class AbstractController {

protected:

	Client *model;
	STATE new_state;

public:
	
	explicit AbstractController(Client *model) : model(model) {}

	virtual void handleInput(int ch)=0;

	virtual void move()=0;

	STATE getNewState() { return this->new_state; }

};

#endif

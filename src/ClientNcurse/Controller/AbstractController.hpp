#ifndef _ABSTRACT_CONTROLLER_HPP
#define _ABSTRACT_CONTROLLER_HPP

#include "../Client.hpp"


class AbstractController {

protected:

	Client *model;

public:
	
	explicit AbstractController(Client *model) : model(model) {}

	virtual void handleInput(int ch)=0;

	virtual void move()=0;

};

#endif

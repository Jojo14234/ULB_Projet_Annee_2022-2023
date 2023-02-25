#ifndef _ABSTRACT_VIEW_HPP
#define _ABSTRACT_VIEW_HPP

#include <ncurses.h>
#include <string>

#include "../Client.hpp"


class AbstractView {

protected:

	Client *model;

public:
	
	AbstractView(Client *model) : model(model) {}

	virtual void draw() = 0;

};

#endif

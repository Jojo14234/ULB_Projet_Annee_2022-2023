#ifndef _CONNECTION_CONTROLLER_HPP
#define _CONNECTION_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/ConnectionView.hpp"


class ConnectionController : public AbstractController {

	ConnectionView* view;

public:

	ConnectionController(Client *model, ConnectionView *view) : AbstractController(model), view(view) {}
	
	void handleInput(int ch) override {
		// TODO: implement
		switch (ch) {
			case KEY_ENTER:
				break;
		}
	}

};

#endif

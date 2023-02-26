#ifndef _CONNECTION_CONTROLLER_HPP
#define _CONNECTION_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/ConnectionView.hpp"


class ConnectionController : public AbstractController {

	enum CONNECTION_STATE { USERNAME=0, PASSWORD=1, DONE=2 };
	CONNECTION_STATE STATE = USERNAME;
	ConnectionView* view;

public:

	ConnectionController(Client *model, ConnectionView *view) : AbstractController(model), view(view) {}
	
	void handleInput(int ch) override {
		// TODO: implement
		switch (STATE) {
		case USERNAME:
			if(ch == '\n') { STATE = PASSWORD; }
			else { view->getUsername()->handleInput(ch); }
			break;
		case PASSWORD:
			if(ch == '\n') { STATE = DONE; }
			else { view->getPassword()->handleInput(ch); }
			break;
		case DONE:
			break;
		}
	}

	void move() {
		switch (STATE) {
		case USERNAME:
			view->getUsername()->move();
			break;
		case PASSWORD:
			view->getPassword()->move();
			break;
		case DONE:
			break;
		}
	}

};

#endif
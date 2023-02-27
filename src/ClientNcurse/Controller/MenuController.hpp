#ifndef _MENU_CONTROLLER_HPP
#define _MENU_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/MenuView.hpp"


class MenuController : public AbstractController {

	enum CONNECTION_STATE { USERNAME=0, PASSWORD=1, DONE=2 };
	CONNECTION_STATE STATE = USERNAME;
	MenuView* view;

public:

	MenuController(Client* model, MenuView* view) : AbstractController(model), view(view) {}
	
	void handleInput(int ch) override {
		// TODO: implement
		switch (ch) {
			case KEY_ENTER:
				break;
		}
		if (view != nullptr) { view->draw(); }
	}

	void move() override {

	}

};

#endif

#ifndef _MENU_CONTROLLER_HPP
#define _MENU_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"


class MenuController : public AbstractController {

public:

	using AbstractController::AbstractController;
	
	void handleInput(int ch) override {
		// TODO: implement
		switch (ch) {
			case KEY_ENTER:
				break;
		}
	}


};

#endif

#ifndef _GAME_CONTROLLER_HPP
#define _GAME_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"


class GameController : public AbstractController {

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

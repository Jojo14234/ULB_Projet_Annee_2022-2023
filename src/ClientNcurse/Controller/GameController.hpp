#ifndef _GAME_CONTROLLER_HPP
#define _GAME_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/GameView.hpp"


class GameController : public AbstractController {

	GameView* view;

public:

	GameController(Client* model, GameView* view) : AbstractController(model), view(view) {}
	
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

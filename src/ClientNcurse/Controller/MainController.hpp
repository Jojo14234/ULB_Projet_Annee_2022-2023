#ifndef _MAIN_CONTROLLER_HPP
#define _MAIN_CONTROLLER_HPP


#include "../Client.hpp"
#include "ConnectionController.hpp"
#include "MenuController.hpp"
#include "GameController.hpp"
#include "../View/MainView.hpp"
#include "../utils.hpp"


class MainController {

	Client *model;
	MainView *view;

	ConnectionController connection{model, view->getConnection()};
	MenuController menu{model, view->getMenu()};
	GameController game{model, view->getGame()};

public:

	MainController(Client *model, MainView* view, Subject* win) : model{model}, view{view} {
		game.setSubject(win);
	}

	void handleInput(STATE &state, int ch) {
		switch (state) {
		case STATE::CONNECTION:
			connection.handleInput(ch);
			state = connection.getNewState();
			break;
		case STATE::MENU:
			menu.handleInput(ch);
			state = menu.getNewState();
			if (state == STATE::GAME) game.init();
			break;
		case STATE::GAME:
			game.handleInput(ch);
			break;
		}
	}

	void move(STATE &state) {
		switch (state) {
		case STATE::CONNECTION:
			connection.move();
			break;
		case STATE::MENU:
			menu.move();
			break;
		case STATE::GAME:
			game.move();
			break;
		}
	}

};

#endif

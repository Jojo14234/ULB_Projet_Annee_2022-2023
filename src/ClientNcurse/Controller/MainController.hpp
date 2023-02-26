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

	ConnectionController connection{model};
	MenuController menu{model};
	GameController game{model};

public:

	MainController(Client *model, MainView* view) : model{model}, view{view} {}

	void handleInput(STATE &state, int ch) {
		switch (state) {
		case STATE::CONNECTION:
			connection.handleInput(ch);
			break;
		case STATE::MENU:
			menu.handleInput(ch);
			break;
		case STATE::GAME:
			game.handleInput(ch);
			break;
		}
	}

};

#endif

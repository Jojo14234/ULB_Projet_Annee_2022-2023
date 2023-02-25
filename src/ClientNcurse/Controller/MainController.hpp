#ifndef _MAIN_CONTROLLER_HPP
#define _MAIN_CONTROLLER_HPP


#include "../Client.hpp"
#include "ConnectionController.hpp"
#include "MenuController.hpp"
#include "GameController.hpp"
#include "../utils.hpp"


class MainController {

	Client *model;

	ConnectionController connection;
	MenuController menu;
	GameController game;

public:

	MainController(Client *model) : model(model) {}

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

#ifndef _MAIN_VIEW_HPP
#define _MAIN_VIEW_HPP

#include "../Client.hpp"
#include "ConnectionView.hpp"
#include "MenuView.hpp"
#include "GameView.hpp"
#include "../utils.hpp"


class MainView {

	Client *model;

	ConnectionView connection{model};
	MenuView menu{model};
	GameView game{model};

public:

	explicit MainView(Client *model) : model(model) {}

	void draw(STATE &state) {
		switch (state) {
		case STATE::CONNECTION:
			connection.draw();
			break;
		case STATE::MENU:
			menu.draw();
			break;
		case STATE::GAME:
			game.draw();
			break;
		}
	}

	// GETTERS
	ConnectionView* getConnection() { return &connection; }
	MenuView* getMenu() { return &menu; }
	GameView* getGame() { return &game; }


};

#endif

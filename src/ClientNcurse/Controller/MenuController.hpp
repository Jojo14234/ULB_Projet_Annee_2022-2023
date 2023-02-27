#ifndef _MENU_CONTROLLER_HPP
#define _MENU_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/MenuView.hpp"


class MenuController : public AbstractController {

	enum MENU_STATE { CONSOLE=0, JOIN=1, IDLE=2 };
	MENU_STATE STATE = IDLE;
	MenuView* view;

public:

	MenuController(Client* model, MenuView* view) : AbstractController(model), view(view) {}
	
	void handleInput(int ch) override {
		// TODO: implement
		if ( ch == KEY_MOUSE ) {
			MEVENT event;
			if (getmouse(&event) != OK) { return; }
			if (event.bstate & BUTTON1_CLICKED) {
				if ( this->view->getConsoleInputBox()->isClicked(Position{event.x, event.y}) ) { this->STATE = CONSOLE; }
				else if ( this->view->getJoinInputBox()->isClicked(Position{event.x, event.y}) ) { this->STATE = JOIN; }
			}
		} else {
			
		}
	}

	void move() override {

	}

};

#endif

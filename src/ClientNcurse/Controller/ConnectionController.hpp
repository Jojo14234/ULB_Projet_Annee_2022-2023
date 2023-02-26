#ifndef _CONNECTION_CONTROLLER_HPP
#define _CONNECTION_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/ConnectionView.hpp"
#include "../Client.hpp"


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
			if(ch == '\n') { this->STATE = PASSWORD; }
			else { this->view->getUsernameInputBox()->handleInput(ch); }
			break;
		case PASSWORD:
			if(ch == '\n') { this->STATE = DONE; }
			else { this->view->getPasswordInputBox()->handleInput(ch); }
			break;
		case DONE:
			if (ch == KEY_MOUSE) {
				MEVENT event;
				if (getmouse(&event) != OK) { break; }
				if (event.bstate && BUTTON1_CLICKED) {
					if ( this->view->getLoginButton()->isClicked(Position{event.x, event.y}) ) {
						std::cout << "Entered login" << std::endl;
						this->model->sendLogin(this->view->getUsernameInputBox()->getText(), this->view->getPasswordInputBox()->getText());
					} else if ( this->view->getRegisterButton()->isClicked(Position{event.x, event.y}) ) {
						std::cout << "Entered register" << std::endl;
						this->model->sendRegister(this->view->getUsernameInputBox()->getText(), this->view->getPasswordInputBox()->getText());
					}
					// TODO: implement reception
				}
			}
		}
	}

	void move() override {
		switch (STATE) {
		case USERNAME:
			view->getUsernameInputBox()->move();
			break;
		case PASSWORD:
			view->getPasswordInputBox()->move();
			break;
		case DONE:
			break;
		}
	}

	void clear() {
		STATE = USERNAME;
		view->clear();
	}

};

#endif

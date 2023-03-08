#ifndef _CONNECTION_CONTROLLER_HPP
#define _CONNECTION_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/ConnectionView.hpp"
#include "../Client.hpp"
#include "../utils.hpp"


class ConnectionController : public AbstractController {

	enum CONNECTION_STATE { USERNAME=0, PASSWORD=1, DONE=2 };
	CONNECTION_STATE state = USERNAME;
	ConnectionView* view;

public:

	ConnectionController(Client *model, ConnectionView *view) : AbstractController(model), view(view) { this->new_state = STATE::CONNECTION; }
	
	void handleInput(int ch) override {
		switch (this->state) {
		case USERNAME:
			if(ch == '\n') { this->state = PASSWORD; }
			else { this->view->getUsernameInputBox()->handleInput(ch); }
			break;
		case PASSWORD:
			if(ch == '\n') { this->state = DONE; }
			else { this->view->getPasswordInputBox()->handleInput(ch); }
			break;
		case DONE:
			if (ch == KEY_MOUSE) {
				MEVENT event;
				if (getmouse(&event) != OK) { break; }
				if (event.bstate & BUTTON1_CLICKED) {
					if ( this->view->getLoginButton()->isClicked(Position{event.x, event.y}) ) {
						this->model->sendLogin(this->view->getUsernameInputBox()->getText(), this->view->getPasswordInputBox()->getText());
					} else if ( this->view->getRegisterButton()->isClicked(Position{event.x, event.y}) ) {
						this->model->sendRegister(this->view->getUsernameInputBox()->getText(), this->view->getPasswordInputBox()->getText());
					} else { break; }
					std::string response;
					this->model->receive(response);
					if (response == "TRUE") { this->new_state = STATE::MENU; }
					this->clear();
				}
			}
		}
	}

	void move() override {
		switch (this->state) {
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

	void clear() { this->state = USERNAME; view->clear(); }

};

#endif

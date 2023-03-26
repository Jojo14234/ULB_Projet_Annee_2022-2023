/**
 * Project Untitled
 */

#include <iostream>

#include "ConnectionCUIController.hpp"
#include "../View/ConnectionCUIView.hpp"
#include "../../Model/Client.hpp"
#include "../../../Server/ClientManager/QUERY.hpp"

// Public

ConnectionCUIController::ConnectionCUIController(Client* model, ConnectionCUIView* view) :
	AbstractCUIController(model, STATE::CONNECTION), view{view} {}

void ConnectionCUIController::handle(int event) {
	switch (this->state) {
	case USERNAME:
		if(event == '\n') { this->state = PASSWORD; }
		else { this->view->username_input_box.handleInput(event); }
		break;
	case PASSWORD:
		if(event == '\n') { this->state = DONE; }
		else { this->view->password_input_box.handleInput(event); }
		break;
	case DONE:
		if (event == KEY_MOUSE) {
			MEVENT event;
			if (getmouse(&event) != OK) { break; }
			if (event.bstate & BUTTON1_CLICKED) {
				if ( this->view->login_button.isClicked(Position{event.x, event.y}) ) {
					this->model->sendLogin(this->view->username_input_box.getText(), this->view->password_input_box.getText());
				} else if ( this->view->register_button.isClicked(Position{event.x, event.y}) ) {
					this->model->sendRegister(this->view->username_input_box.getText(), this->view->password_input_box.getText());
				} else { break; }
				std::string response;
				QUERY query = this->model->receive(response);
				if ( query == QUERY::TRUEQ ) { this->new_state = STATE::MENU; }
				this->clear();
			}
		}
	}
}

void ConnectionCUIController::move() {
	switch (this->state) {
	case USERNAME:
		view->username_input_box.move();
		break;
	case PASSWORD:
		view->password_input_box.move();
		break;
	case DONE:
		break;
	}
}

void ConnectionCUIController::clear() {
	this->state = USERNAME;
	view->clear();
}
#include <SFML/Window.hpp>

#include "ConnectionGUIController.hpp"
#include "../View/ConnectionGUIView.hpp"
#include "../../../Server/ClientManager/QUERY.hpp"
#include "../../Model/Client.hpp"


void ConnectionGUIController::handle(sf::Event event) {
	switch(event.type) {
		case sf::Event::MouseButtonPressed: {
			// buttons
			if (this->view->login_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->model->sendLogin(this->view->username.getText(), this->view->password.getText());
				if (this->model->receive() == QUERY::TRUEQ) { this->new_state = STATE::MENU; }
				this->view->clear();
			} else if (this->view->register_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->model->sendRegister(this->view->username.getText(), this->view->password.getText());
				if (this->model->receive() == QUERY::TRUEQ) { this->new_state = STATE::MENU; }
				this->view->clear();
			} else {
				this->view->username.deselect();
				this->view->password.deselect();
				if (this->view->username.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->state = USERNAME;
					this->view->username.select();
				} else if (this->view->password.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->state = PASSWORD;
					this->view->password.select();
				} 
			} break;
		}
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed: {
			switch(this->state) {
				case USERNAME: this->view->username.handle(event); break;
				case PASSWORD: this->view->password.handle(event); break;
				case DONE: break;
			}
		}
		default: break;
	}
}

void ConnectionGUIController::clear() {
	
}

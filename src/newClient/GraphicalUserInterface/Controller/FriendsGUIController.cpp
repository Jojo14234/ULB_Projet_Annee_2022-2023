#include <SFML/Window.hpp>

#include "FriendsGUIController.hpp"


void FriendsGUIController::handle(sf::Event event) {
	switch(event.type) {
		case sf::Event::MouseButtonPressed: {
			// TODO buttons
			if (this->view->back_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->new_state = STATE::MENU;
			} else if (true) {
				// TODO
			} else {
				// TODO
			} break;
		}
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed: {
			// TODO
		}
		default: break;
	}
}

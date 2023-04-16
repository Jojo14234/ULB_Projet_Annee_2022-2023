#include <SFML/Window.hpp>

#include "FriendsGUIController.hpp"
#include "../View/FriendsGUIView.hpp"
#include "../../Model/Client.hpp"


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
			break;
		}
		case sf::Event::MouseWheelMoved: {
			if (this->view->scroll.contains(event.mouseWheel.x, event.mouseWheel.y)) {
				if (event.mouseWheel.delta > 0) this->view->scroll.scrollUp();
				else this->view->scroll.scrollDown();
			}
		}
		default: break;
	}
}
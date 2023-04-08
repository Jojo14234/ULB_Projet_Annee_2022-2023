#include <SFML/Window.hpp>

#include "MenuGUIController.hpp"
#include "../View/MenuGUIView.hpp"
#include "../configs.hpp"


void MenuGUIController::handle(sf::Event event) {
	if (event.type != sf::Event::MouseButtonPressed) return;
	// buttons
	if (this->view->quit_button.contains(event.mouseButton.x, event.mouseButton.y)) {
		// TODO
	} else if (this->view->join.contains(event.mouseButton.x, event.mouseButton.y)) {
		// TODO
	} else if (this->view->create.contains(event.mouseButton.x, event.mouseButton.y)) {
		this->new_state = STATE::CREATE;
	} else if (this->view->rank.contains(event.mouseButton.x, event.mouseButton.y)) {
		this->new_state = STATE::RANK;
	} else if (this->view->friend_menu.contains(event.mouseButton.x, event.mouseButton.y)) {
		this->new_state = STATE::FRIENDS;
	} else if (this->view->settings.contains(event.mouseButton.x, event.mouseButton.y)) {
		this->new_state = STATE::SETTINGS;
	}
}

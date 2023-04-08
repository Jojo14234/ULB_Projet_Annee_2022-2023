#include <SFML/Window.hpp>

#include "MenuGUIController.hpp"
#include "../View/MenuGUIView.hpp"
#include "../../Model/Client.hpp"
#include "../configs.hpp"


void MenuGUIController::handle(sf::Event event) {
	if (event.type != sf::Event::MouseButtonPressed) return;
	// buttons
	if (this->view->settings_popup.isVisible()) {
		if (this->view->settings_popup.getButton(0)->contains(event.mouseButton.x, event.mouseButton.y)) {
			// TODO
			// back button
			this->view->settings_popup.setHidden();
		} else if (this->view->settings_popup.getButton(1)->contains(event.mouseButton.x, event.mouseButton.y)) {
			// TODO
			// ok button
		}
	} else {
		if (this->view->quit_button.contains(event.mouseButton.x, event.mouseButton.y)) {
			this->new_state = STATE::CONNECTION;
			this->model->disconnectAccount();
		} else if (this->view->join.contains(event.mouseButton.x, event.mouseButton.y)) {
			// TODO
		} else if (this->view->create.contains(event.mouseButton.x, event.mouseButton.y)) {
			this->new_state = STATE::CREATE;
		} else if (this->view->rank.contains(event.mouseButton.x, event.mouseButton.y)) {
			this->new_state = STATE::RANK;
		} else if (this->view->friend_menu.contains(event.mouseButton.x, event.mouseButton.y)) {
			this->new_state = STATE::FRIENDS;
		} else if (this->view->settings.contains(event.mouseButton.x, event.mouseButton.y)) {
			this->view->settings_popup.setVisible();
		}
	}
}

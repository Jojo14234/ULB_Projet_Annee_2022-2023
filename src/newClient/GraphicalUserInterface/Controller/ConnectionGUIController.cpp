#include <SFML/Window.hpp>

#include "ConnectionGUIController.hpp"
#include "../View/ConnectionGUIView.hpp"


void ConnectionGUIController::handle(sf::Event event) {
	this->view->username.handle(event);
}

void ConnectionGUIController::clear() {
	
}

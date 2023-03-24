#include <SFML/Window.hpp>

#include "ConnectionUIController.hpp"
#include "../View/ConnectionUIView.hpp"


void ConnectionUIController::handle(sf::Event event) {
	this->view->username.handle(event);
}

void ConnectionUIController::clear() {
	
}

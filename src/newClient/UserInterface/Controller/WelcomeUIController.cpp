#include <SFML/Window.hpp>
#include <iostream>
#include "WelcomeUIController.hpp"


void WelcomeUIController::handle(sf::Event event) {
	switch(event.type) {
	case sf::Event::KeyPressed:
	case sf::Event::MouseButtonPressed: this->new_state = STATE::CONNECTION;
	default: break;
	}
}

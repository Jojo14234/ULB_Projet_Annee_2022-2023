#include <SFML/Window.hpp>
#include <iostream>
#include "WelcomeGUIController.hpp"


void WelcomeGUIController::handle(sf::Event event) {
	switch(event.type) {
	case sf::Event::KeyPressed:
	case sf::Event::MouseButtonPressed: this->new_state = STATE::FRIENDS;
	default: break;
	}
}

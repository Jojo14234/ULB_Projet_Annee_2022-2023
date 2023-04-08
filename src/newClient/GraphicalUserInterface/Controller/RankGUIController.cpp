#include <SFML/Window.hpp>

#include "RankGUIController.hpp"
#include "../View/RankGUIView.hpp"
#include "../../Model/Client.hpp"


void RankGUIController::handle(sf::Event event) {
	if (event.type != sf::Event::MouseButtonPressed) return;
	if (this->view->back_button.contains(event.mouseButton.x, event.mouseButton.y)) {
		this->new_state = STATE::MENU;
	} else if ( this->view->top.contains(event.mouseButton.x, event.mouseButton.y)) {
        this->view->hideMyRank();
		this->view->showTop();
    } else if (this->view->my_rank.contains(event.mouseButton.x, event.mouseButton.y)) {
        this->view->hideTop();
		this->view->showMyRank();
    }
}

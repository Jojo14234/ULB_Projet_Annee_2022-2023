#include <SFML/Window.hpp>
#include <string>
#include <vector>

#include "FriendsGUIController.hpp"
#include "../View/FriendsGUIView.hpp"
#include "../../Model/Client.hpp"
#include "../../../utils/Configs.hpp"


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


void FriendsGUIController::update() {
	// TODO
	this->model->sendQuery(QUERY_TYPE::FRIENDS_INFO);
	std::vector<std::string> friends_name;
	std::vector<std::string> friends_requests;
	this->model->receiveFriendsInfo(friends_name, friends_requests);

}

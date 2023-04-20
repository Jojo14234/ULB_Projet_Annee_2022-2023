#include <SFML/Window.hpp>
#include <string>
#include <vector>

#include "FriendsGUIController.hpp"
#include "../View/FriendsGUIView.hpp"
#include "../../Model/Client.hpp"
#include "../../../Utils/Config/Configs.hpp"


void FriendsGUIController::handle(sf::Event event) {
	switch(event.type) {
		case sf::Event::MouseButtonPressed: {
			// TODO popup
			if (this->view->request_popup.isVisible()) {
				if (this->view->request_popup.getButton(0).contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->request_popup.setHidden();
				} else if (true) {
					// TODO
				}

			} else if (this->view->ask_popup.isVisible()) {
				if (this->view->ask_popup.getButton(0).contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->ask_popup.setHidden();
				} else if (true) {
					// TODO
				}


			} else if (this->view->back_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->new_state = STATE::MENU;
			} else if (this->view->send_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				std::string msg = this->view->message_input.getString();
				if (msg.length()==0) break; 
				this->model->sendCommand(MainInputParser{"/msg " + this->view->other_user.getString() + " " + msg});
				if (this->model->receive() == QUERY::TRUEQ) {
					this->view->addMsg(msg);
				}
			} else {
				for (const auto &friend_box : this->view->friend_list) {
					if (friend_box.msgBtnContains(event.mouseButton.x, event.mouseButton.y)) {
						this->view->other_user.setString(friend_box.getUsername());
					} else if (friend_box.rmvBtnContains(event.mouseButton.x, event.mouseButton.y)) {
						this->model->sendCommand(MainInputParser{"/f remove " + friend_box.getUsername()});
						if (this->model->receive() == QUERY::TRUEQ) {
							this->view->friend_list.remove(friend_box);
						}
					}
				}
			} break;
		}
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed: {
			if (this->view->ask_popup.isVisible()) {
				this->view->ask_popup.getInput(0).handle(event);
			} else { this->view->message_input.handle(event); }
			break;
		}
		case sf::Event::MouseWheelMoved: {
			if (this->view->friend_list.contains(event.mouseWheel.x, event.mouseWheel.y)) {
				if (event.mouseWheel.delta > 0) this->view->friend_list.scrollUp();
				else this->view->friend_list.scrollDown();
			}
		}
		default: break;
	}
}


void FriendsGUIController::update() {
	this->model->sendQuery(QUERY_TYPE::FRIENDS_INFO);
	std::vector<std::string> friends_name;
	std::vector<std::string> friends_requests;
	this->model->receiveFriendsInfo(friends_name, friends_requests);
}

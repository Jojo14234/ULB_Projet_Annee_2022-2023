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
			this->view->message_input.deselect();
			if (this->view->request_popup.isVisible()) {
				if (this->view->request_popup.getButton(0)->contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->request_popup.setHidden();
				} else if (this->view->request_popup.getSelector(0)->getLButton()->contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->request_popup.getSelector(0)->getLButton()->click();
				} else if (this->view->request_popup.getSelector(0)->getRButton()->contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->request_popup.getSelector(0)->getRButton()->click();
				} else if (this->view->request_popup.getSelector(0)->size() > 0) {
					if (this->view->request_popup.getButton(1)->contains(event.mouseButton.x, event.mouseButton.y)) {
						this->model->sendCommand(MainInputParser{"/f accept " + this->view->request_popup.getSelector(0)->getActualString()});
					} else if (this->view->request_popup.getButton(2)->contains(event.mouseButton.x, event.mouseButton.y)) {
						this->model->sendCommand(MainInputParser{"/f refuse " + this->view->request_popup.getSelector(0)->getActualString()});
					}
				}
			} else if (this->view->ask_popup.isVisible()) {
				this->view->ask_popup.getInput(0)->deselect();
				if (this->view->ask_popup.getButton(0)->contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->ask_popup.setHidden();
				} else if (this->view->ask_popup.getInput(0)->contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->ask_popup.getInput(0)->select();
				} else if (this->view->ask_popup.getButton(1)->contains(event.mouseButton.x, event.mouseButton.y)) {
					std::string username = this->view->ask_popup.getInput(0)->getString();
					if (username.length() < 5) break;
					this->model->sendCommand(MainInputParser{"/f add " + username});
					if (this->model->receive() == QUERY::TRUEQ) {
						this->view->ask_popup.setHidden();
					}
				}
			} else if (this->view->request_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->view->request_popup.setVisible();
			} else if (this->view->ask_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->view->ask_popup.setVisible();
			} else if (this->view->back_button.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->new_state = STATE::MENU;
			} else if (this->view->message_input.contains(event.mouseButton.x, event.mouseButton.y)) {
				this->view->message_input.select();
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
				this->view->ask_popup.getInput(0)->handle(event);
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
	this->view->clear();
	this->model->sendQuery(QUERY_TYPE::FRIENDS_INFO);
	std::vector<std::string> friends_name;
	std::vector<std::string> friends_requests;
	this->model->receiveFriendsInfo(friends_name, friends_requests);
	// TODO remplir scrollbox
	for (const auto &name : friends_requests) {
		this->view->request_popup.getSelector(0)->addChoice(name);
	}

	const double size_x = WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f;
	const double size_y = WINDOW_WIDTH/20.f;
	const double pos_x = WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18;
	const double pos_y = WINDOW_WIDTH/30.f + WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5.+WINDOW_WIDTH/50.f;
	const int sep = WINDOW_WIDTH/160.f;
	int i = 0;
	for (const auto &name : friends_name) {
		this->view->friend_list.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y +((sep + size_y)*i) ), name});
		i++;
	}

	this->view->addMsg("Miaou Miaou", "yoyo");
}

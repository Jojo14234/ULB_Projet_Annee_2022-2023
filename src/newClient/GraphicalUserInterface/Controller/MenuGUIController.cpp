#include <SFML/Window.hpp>

#include "MenuGUIController.hpp"
#include "../View/MenuGUIView.hpp"
#include "../../Model/Client.hpp"
#include "../configs.hpp"

#include <string>

void MenuGUIController::handle(sf::Event event) {
	//if (event.type != sf::Event::MouseButtonPressed) return;
	// buttons
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			if (this->view->settings_popup.isVisible()) {
				// back button
				if (this->doSettingBtnNContain(0, event)) { this->view->settings_popup.setHidden(); break; }
				// ok button
				if (this->doSettingBtnNContain(1, event)) { break; /*TODO*/ }
				// left button window size
				if (this->doSettingBtnNContain(0, event, false)) { this->view->settings_popup.getSelector(0)->getLButton()->click(); break;}
				// right button window size
				if (this->doSettingBtnNContain(0, event, true)) { this->view->settings_popup.getSelector(0)->getRButton()->click(); break;}
				break;
			}
			else if (this->view->create_popup.isVisible()) {
				// back button
				if (this->doCreatePopUpBtnNContain(0, event)) { this->view->create_popup.setHidden(); break; }
				// ok button
				if (this->doCreatePopUpBtnNContain(1, event)) { this->createProcess(); break; }
				for (int i = 0; i < 5; i++) {
					if (this->doCreatePoUpSelectorNContain(i, event, false)) { this->createPopUpClick(i, false); break; }
					if (this->doCreatePoUpSelectorNContain(i, event, true)) { this->createPopUpClick(i, true); break; }
				}
				break;
			}
			else if (this->view->join_popup.isVisible()) {
				// back button
				if (this->doJoinPopUpNBtnContain(0, event)) { this->view->join_popup.setHidden(); break; }
				// ok button
				if (this->doJoinPopUpNBtnContain(1, event)) {
					this->joinProcess();
					break; /*TODO*/ }

				// Other
				this->view->join_popup.getInput(0)->deselect();
				if (this->view->join_popup.getInput(0)->contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->join_popup.getInput(0)->select();
				}
				break;
			}
			else {
				// Quit
				if (this->view->quit_button.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->quit_button.playSound();
					this->new_state = STATE::CONNECTION;
					this->model->disconnectAccount();
				}
				// Join
				else if (this->view->join.isVisible() and this->view->join.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->join.playSound();
					this->view->join_popup.setVisible();
				}
				// Create
				else if (this->view->create.isVisible() and this->view->create.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->create.playSound();
					this->view->create_popup.setVisible();
				}
				// Rank
				else if (this->view->rank.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->rank.playSound();
					this->new_state = STATE::RANK;
				}
				// Friends
				else if (this->view->friend_menu.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->friend_menu.playSound();
					this->new_state = STATE::FRIENDS;
					this->friend_controller->update();
				}
				// Settings
				else if (this->view->settings.contains(event.mouseButton.x, event.mouseButton.y)) {
					this->view->settings.playSound();
					this->view->settings_popup.setVisible();
				}
				break;
			}
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed: this->view->join_popup.getInput(0)->handle(event); break;
		default: break;
	}
}


bool MenuGUIController::doSettingBtnNContain(int n, sf::Event event) {
	return this->view->settings_popup.getButton(n)->contains(event.mouseButton.x, event.mouseButton.y);
}

bool MenuGUIController::doSettingBtnNContain(int n, sf::Event event, bool right_side) {
	if (right_side) { return this->view->settings_popup.getSelector(n)->getRButton()->contains(event.mouseButton.x, event.mouseButton.y); }
	return this->view->settings_popup.getSelector(n)->getLButton()->contains(event.mouseButton.x, event.mouseButton.y);
}

bool MenuGUIController::doCreatePopUpBtnNContain(int n, sf::Event event) {
	return this->view->create_popup.getButton(n)->contains(event.mouseButton.x, event.mouseButton.y);
}

bool MenuGUIController::doCreatePoUpSelectorNContain(int n, sf::Event event, bool right_side) {
	if (right_side) { return this->view->create_popup.getSelector(0)->getRButton()->contains(event.mouseButton.x,event.mouseButton.y); }
	return this->view->create_popup.getSelector(n)->getLButton()->contains(event.mouseButton.x,event.mouseButton.y);
}

void MenuGUIController::createPopUpClick(int n, bool right_side) {
	if (right_side) { this->view->create_popup.getSelector(n)->getRButton()->click(); }
	else { this->view->create_popup.getSelector(n)->getLButton()->click(); }
}

void MenuGUIController::createProcess() {
	std::string cmd = this->view->getCreateCmd();
	this->model->sendCommand(MainInputParser{cmd});
	this->new_state = STATE::GAME;
	this->game_controller->update();
}

void MenuGUIController::joinProcess() {
	std::string cmd = "/join " + this->view->join_popup.getInput(0)->getString();
	this->model->sendCommand(MainInputParser{cmd});
	if (this->model->receive() == QUERY::TRUEQ) {
		this->new_state = STATE::GAME;
		this->game_controller->update();
	}
}

bool MenuGUIController::doJoinPopUpNBtnContain(int n, sf::Event event) {
	return this->view->join_popup.getButton(n)->contains(event.mouseButton.x, event.mouseButton.y);
}


#include <SFML/Window.hpp>

#include "ConnectionGUIController.hpp"
#include "../View/ConnectionGUIView.hpp"
#include "../../Model/Client.hpp"
#include "../../../Server/ClientManager/QUERY.hpp"


ConnectionGUIController::ConnectionGUIController(Client* model, ConnectionGUIView* view) : AbstractGUIController(model, STATE::CONNECTION), view{view} {view->playMusic();}

void ConnectionGUIController::handle(sf::Event event) {
	switch(event.type) {
        // Btn pressed
		case sf::Event::MouseButtonPressed:
            // Unselect all
            this->view->username.deselect();
            this->view->password.deselect();

			// Which btn was pressed
			if (this->doLoginBtnContain(event))     { this->loginProcess(); break; }
            if (this->doRegisterBtnContain(event))  { this->registerProcess(); break; }
            if (this->doDisconnectBtnContain(event))  { this->disconnectProcess(); break; }
            if (this->doUsernameContain(event))     { this->usernameProcess(); break; }
            if (this->doPasswordContain(event))     { this->passwordProcess(); break; }
            break;
        // Key pressed or text entered
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed:
			this->keyPressProcess(event); break;

        // else
		default: break;
	}
}

bool ConnectionGUIController::doLoginBtnContain(sf::Event event) {
    if (this->view->login_button.contains(event.mouseButton.x, event.mouseButton.y)) {
        this->view->login_button.playSound();
        this->view->stopMusic();
        return true;   
    }
    return false;
}
bool ConnectionGUIController::doRegisterBtnContain(sf::Event event) {
    if (this->view->register_button.contains(event.mouseButton.x, event.mouseButton.y)) {
        this->view->register_button.playSound();
        this->view->stopMusic();
        return true;   
    }
    return false;
}

bool ConnectionGUIController::doDisconnectBtnContain(sf::Event event) {
    if (this->view->disconnect_button.contains(event.mouseButton.x, event.mouseButton.y)) {
        this->view->disconnect_button.playSound();
        this->view->stopMusic();
        return true;
    }
    return false;
}
bool ConnectionGUIController::doUsernameContain(sf::Event event) {
    return this->view->username.contains(event.mouseButton.x, event.mouseButton.y);
}
bool ConnectionGUIController::doPasswordContain(sf::Event event) {
    return this->view->password.contains(event.mouseButton.x, event.mouseButton.y);
}

void ConnectionGUIController::loginProcess() {
    this->model->sendLogin(this->view->username.getText(), this->view->password.getText());
    if (this->model->receive() == QUERY::TRUEQ) { this->new_state = STATE::MENU; }
    this->view->clear();
}
void ConnectionGUIController::registerProcess() {
    this->model->sendRegister(this->view->username.getText(), this->view->password.getText());
    if (this->model->receive() == QUERY::TRUEQ) { this->new_state = STATE::MENU; }
    this->view->clear();
}

void ConnectionGUIController::disconnectProcess() {
    this->model->sendDisconnect();
    if (this->model->receive() == QUERY::DISCONNECT) { exit(0); }
}
void ConnectionGUIController::usernameProcess() {
    this->state = USERNAME;
    this->view->username.select();
}
void ConnectionGUIController::passwordProcess() {
    this->state = PASSWORD;
    this->view->password.select();
}

void ConnectionGUIController::keyPressProcess(sf::Event event) {
    switch(this->state)  {
        case USERNAME:  this->view->username.handle(event); break;
        case PASSWORD:  this->view->password.handle(event); break;
        case DONE:      break;
        default:        break;
    }
}
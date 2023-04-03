/**
 * Project Untitled
 */

#include <ncurses.h>
#include <string>

#include "MenuTerminalController.hpp"
#include "../View/MenuTerminalView.hpp"
#include "../../Model/InputParser/MainInputParser.hpp"
#include "../../Model/Client.hpp"
#include "../View/Objects.hpp"

// Public

MenuTerminalController::MenuTerminalController(Client* model, MenuTerminalView* view) :
	AbstractTerminalController(model, STATE::MENU), view{view} {}

void MenuTerminalController::handle(int event) {
	switch(event) {
	case KEY_MOUSE:
		MEVENT mevent;
		if (getmouse(&mevent) != OK) { break; }
		if (mevent.bstate & BUTTON1_CLICKED) {
			if ( this->view->console.isClicked(Position{mevent.x, mevent.y}) ) { this->state = CONSOLE; }
			else if ( this->view->join.isClicked(Position{mevent.x, mevent.y}) ) { this->state = JOIN; }
			else { this->state = IDLE; }
		} break;
	case '\n':
		switch(this->state) {
		case CONSOLE: {
			this->view->console.addInput();
			MainInputParser parser(this->view->console.getInput());
			std::string response;
			if (this->model->sendCommand(parser)) { QUERY query = this->model->receive(response); }
			else { response = "La commande n'existe pas"; }
			this->view->console.addText(response);


			if (parser.getQueryType() == QUERY_TYPE::CREATE_GAME){
				this->new_state = STATE::GAME;
				int gamecode = atoi(&response[response.length()-4]);
				this->model->setGameCode(gamecode);
				this->model->createGame();
			}
			break; }
		case JOIN: {
			this->model->sendJoinGame(this->view->join.getValue());
			std::string response;
			QUERY query = this->model->receive(response);
			this->view->console.addText(response);
			if (response != "aucune partie n'existe avec ce code"){
				this->new_state = STATE::GAME;
				this->model->setGameCode(this->view->join.getValue());
			}
			break; }
		case IDLE: break;
		} break;
	default:
		switch (this->state) {
		case CONSOLE: this->view->console.handleInput(event); break;
		case JOIN: this->view->join.handleInput(event); break;
		case IDLE: break;
		} break;
	}
}

void MenuTerminalController::move() {
	switch (this->state) {
	case CONSOLE: this->view->console.move(); break;
	case JOIN: this->view->join.move(); break;
	case IDLE: break;
	}
}
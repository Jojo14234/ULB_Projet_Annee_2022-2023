#ifndef _GAME_CONTROLLER_HPP
#define _GAME_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/GameView.hpp"


class GameController : public AbstractController {

	enum MENU_STATE { CHAT, CONSOLE, IDLE };
	MENU_STATE STATE = IDLE;
	GameView* view;

public:

	GameController(Client* model, GameView* view) : AbstractController(model), view(view) {}
	
	void handleInput(int ch) override {
		switch(ch) {
		case KEY_MOUSE:
			MEVENT event;
			if (getmouse(&event) != OK) { break; }
			if (event.bstate & BUTTON1_CLICKED) {
				if ( this->view->getConsole()->isClicked(Position{event.x, event.y}) ) { this->STATE = CONSOLE; }
				else if ( this->view->getChat()->isClicked(Position{event.x, event.y}) ) { this->STATE = CHAT; }
				else { this->STATE = IDLE; }
			} break;

		case '\n':
			switch(this->STATE) {
			case CONSOLE: {
				this->view->getConsole()->addInput();
				InputParser parser(this->view->getConsole()->getInput());
				std::string response;
				if (this->model->sendCommand(parser)) { this->model->receive(response); }
				else { response = "La commande n'existe pas"; }
				this->view->getConsole()->addText(response);
				break; }
			case CHAT: {
				this->view->getChat()->addInput();
				InputParser parser(this->view->getChat()->getInput());
				std::string response;
				if (this->model->sendCommand(parser)) { this->model->receive(response); }
				else { response = "La commande n'existe pas"; }
				this->view->getChat()->addText(response);
				break; }
			
			case IDLE: break;
			} break;
		
		default:
			switch (this->STATE) {
			case CONSOLE: this->view->getConsole()->handleInput(ch); break;
			case CHAT: this->view->getChat()->handleInput(ch); break;
			case IDLE: break;
			} break;
		}
	}

	void move() override {
		switch (this->STATE) {
		case CHAT: this->view->getChat()->move(); break;
		case CONSOLE: this->view->getConsole()->move(); break;
		case IDLE: break;
		}
	}

};

#endif

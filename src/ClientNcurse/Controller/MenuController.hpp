#ifndef _MENU_CONTROLLER_HPP
#define _MENU_CONTROLLER_HPP

#include <ncurses.h>

#include "AbstractController.hpp"
#include "../View/MenuView.hpp"
#include "../InputParser/MainInputParser.hpp"


class MenuController : public AbstractController {

	enum MENU_STATE { CONSOLE, JOIN, IDLE };
	MENU_STATE STATE = IDLE;
	MenuView* view;

public:

	MenuController(Client* model, MenuView* view) : AbstractController(model), view(view) { this->new_state = STATE::MENU; }
	
	void handleInput(int ch) override {
		switch(ch) {
		case KEY_MOUSE:
			MEVENT event;
			if (getmouse(&event) != OK) { break; }
			if (event.bstate & BUTTON1_CLICKED) {
				if ( this->view->getConsoleInputBox()->isClicked(Position{event.x, event.y}) ) { this->STATE = CONSOLE; }
				else if ( this->view->getJoinInputBox()->isClicked(Position{event.x, event.y}) ) { this->STATE = JOIN; }
				else { this->STATE = IDLE; }
			} break;

		case '\n':
			switch(this->STATE) {
			case CONSOLE: {
				this->view->getConsoleInputBox()->addInput();
				MainInputParser parser(this->view->getConsoleInputBox()->getInput());
				std::string response;
				if (this->model->sendCommand(parser)) { this->model->receive(response); }
				else { response = "La commande n'existe pas"; }
				this->view->getConsoleInputBox()->addText(response);


				if (parser.getQueryType() == QUERY_TYPE::CREATE_GAME){
					this->new_state = STATE::GAME;
					int gamecode = atoi(&response[response.length()-4]);
					this->model->setGameCode(gamecode);
					this->model->createGame();
				}

				break; }
			case JOIN: {
				this->model->sendJoinGame(this->view->getJoinInputBox()->getValue());
				std::string response;
				this->model->receive(response);
				this->view->getConsoleInputBox()->addText(response);

				if (response != "aucune partie n'existe avec ce code"){
					this->new_state = STATE::GAME;
					this->model->setGameCode(this->view->getJoinInputBox()->getValue());
				}

				break; }
			
			case IDLE: break;
			} break;
		
		default:
			switch (this->STATE) {
			case CONSOLE: this->view->getConsoleInputBox()->handleInput(ch); break;
			case JOIN: this->view->getJoinInputBox()->handleInput(ch); break;
			case IDLE: break;
			} break;
		}
	}

	void move() override {
		switch (this->STATE) {
		case CONSOLE: this->view->getConsoleInputBox()->move(); break;
		case JOIN: this->view->getJoinInputBox()->move(); break;
		case IDLE: break;
		}
	}


};

#endif

#ifndef _GAME_CONTROLLER_HPP
#define _GAME_CONTROLLER_HPP

#include <ncurses.h>
#include <thread>
#include <vector>
#include <string>

#include "AbstractController.hpp"
#include "../View/GameView.hpp"
#include "../InputParser/GameInputParser.hpp"
#include "../InputParser/GameStateParser.hpp"
#include "../InputParser/GameStartParser.hpp"


class GameController : public AbstractController {

	enum MENU_STATE { CHAT, CONSOLE, IDLE };
	MENU_STATE STATE = IDLE;
	GameView* view;
	
	int player_nb ;
	std::vector<std::string> players_username;

public:

	GameController(Client* model, GameView* view) : AbstractController(model), view(view) { this->new_state = STATE::GAME; }
	
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
				GameInputParser parser(this->view->getConsole()->getInput());
				/*
				std::string response;
				if (this->model->sendCommand(parser)) { this->model->receive(response); }
				else { response = "La commande n'existe pas"; }
				this->view->getConsole()->addText(response);
				*/
				if ( not this->model->sendCommand(parser)) this->view->getConsole()->addText("La commande n'existe pas");
				/*if (parser.getQueryType() == GAME_QUERY_TYPE::START && this->model->isCreator()){
					startGame();
					//if (this->model->isCreator()){this->view->getOwnerWaitingText()->setHidden();} 
					//else {this->view->getPlayersWaitingText()->setHidden();}
					}*/
				break; }
				
			case CHAT: {
				this->view->getChat()->addInput();
				MainInputParser parser(this->view->getChat()->getInput());
				/*
				std::string response;
				if (this->model->sendCommand(parser)) { this->model->receive(response); }
				else { response = "La commande n'existe pas"; }
				this->view->getChat()->addText(response);
				*/
				if (not this->model->sendCommand(parser)) this->view->getChat()->addText("La commande n'existe pas");
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

	void receiveMessagesLoop() {
		
		while (this->new_state == STATE::GAME) {
			std::string response;
			this->model->receive(response);

			//start game
			if (response[0] == 'S' &&  response[1] == 'I'){
				GameStartParser start_parser(response);
				start_parser.parse();
				player_nb = start_parser.getBufferSplit().player_nb;
				players_username = start_parser.getBufferSplit().player_usernames;
				startGame();
			}

			//move player + set up money
			else if (response[0] == 'G' && response[1] == 'M') {
				GameStateParser parser(response);

				for (int i = 1; i <= player_nb; i++){
					parser.parseStateLine(player_nb);
					parser.parsePropertiesLine(player_nb);
					this->view->getBoard()->unsetPlayer(i);
					this->view->getBoard()->setPlayer(parser.getBufferSplit().state[i-1][0], i);
					for (int j = 0; j < parser.getBufferSplit().info[i-1].size();j++){
						int index = this->view->getBoard()->getCellIndex(parser.getBufferSplit().info[i-1][j].name);
						if (parser.getBufferSplit().info[i-1][j].level == 0){
							this->view->getBoard()->setPurchased(index, parser.getBufferSplit().info[i-1][j].owner);}
						else{this->view->getBoard()->setHouse(index, 2);} //pas encore tester
						} 
					

					this->view->getInfo()->setMoney( i,parser.getBufferSplit().state[i-1][1]);
				}} 
			//add text on console
			else{
				this->view->getConsole()->addText(response);
			}
				
			
		}
	}
	
	void init() {
		this->initScreen();
		// create a thread to receive messages
		std::thread send_thread(&GameController::receiveMessagesLoop, this);
		send_thread.detach();
	}

	void initScreen() {
		this->view->getDice1()->setHidden();
		this->view->getDice2()->setHidden();

		if (this->model->isCreator()){
			this->view->getOwnerWaitingText()->addText("Gamecode : " + std::to_string(this->model->getGameCode()));
			this->view->getPlayersWaitingText()->setHidden();
		} else {
			this->view->getPlayersWaitingText()->addText("Gamecode : " + std::to_string(this->model->getGameCode()));
			this->view->getOwnerWaitingText()->setHidden();
		}
	}

	void startGame() {
		this->view->getDice1()->setVisible();
		this->view->getDice2()->setVisible();
		this->view->getPlayersWaitingText()->setHidden();
		this->view->getOwnerWaitingText()->setHidden();
		for (int i = 1; i<= player_nb; i++) {
			this->view->getBoard()->setPlayer(0, i);
			this->view->getInfo()->addPlayer(players_username[i-1]);
		}
	}

};

#endif

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
#include "../utils.hpp"
#include "../InputParser/GameLaunchingParser.hpp"

class GameController : public AbstractController {

	enum MENU_STATE { CHAT, CONSOLE, IDLE };
	MENU_STATE STATE = IDLE;
	GameView* view;
	Subject* win;

	int player_nb;
	std::vector<std::string> players_username;

	void hideDice(){
		this->clearDice();
		this->view->getDice1()->setHidden();
		this->view->getDice2()->setHidden();
	}

	void showDice(){
		this->clearDice();
		this->view->getDice1()->setVisible();
		this->view->getDice2()->setVisible();
	}

	void clearDice(){
		this->view->getDice1()->clearResult();
		this->view->getDice2()->clearResult();
	}

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
				if ( not this->model->sendCommand(parser)) this->view->getConsole()->addText("La commande n'existe pas");
				break; }
				
			case CHAT: {
				this->view->getChat()->addInput();
				MainInputParser parser(this->view->getChat()->getInput());
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

	void receiveMessagesLoop(){
		while (this->new_state == STATE::GAME) {
			std::string response;
			QUERY cury;
			this->model->receiveQueryMsg(response, cury);
			
			switch(cury){
				case QUERY::INFOS_START: {
					GameLaunchingParser start_parser(response);
					PlayersInformations p_i = start_parser.parseStartInfo();
					player_nb = p_i.player_nb;
					players_username = p_i.player_usernames;
					this->gameStartUpdate(p_i.beginner); 
					break;
				}

				case QUERY::PLAYER_JOIN_GAME: {
					GameLaunchingParser start_parser(response);
					PlayersInformations p_i = start_parser.parseJoinInfo();
					player_nb = p_i.player_nb;
					players_username = p_i.player_usernames;
					this->playerJoinUpdate();
					break;
				}

				case QUERY::INFOS_ROLL_DICE: {
					GameStateParser game_parser(response);
					DiceInformations d_i = game_parser.parseDiceLine();
					this->view->getDice1()->setText(std::to_string(d_i.first_value), 0);
					this->view->getDice2()->setText(std::to_string(d_i.second_value), 0);
					break;
				}

				case QUERY::INFOS_GAME: {
					GameStateParser game_parser(response);
					std::vector<PlayerInformations> players = game_parser.parseEndTurnLine(player_nb);
					for (int i = 0; i < player_nb; i++){
						this->view->getBoard()->unsetPlayer(i+1);
						this->view->getBoard()->setPlayer(players[i].position, i+1);
						for (unsigned int j = 0; j < players[i].properties.size(); j++){
							int index = this->view->getBoard()->getCellIndex(players[i].properties[j].name);
							if (players[i].properties[j].level == 0){
								this->view->getBoard()->setPurchased(index, i+1);
							}
							else this->view->getBoard()->setHouse(index, 2);
						} 
						
						this->view->getInfo()->setMoney(i+1, players[i].money);
					}
					break;
				}	

				case QUERY::INFOS_NEW_TURN: {
					if (response == this->model->getUsername()) { this->showDice(); }
					else { this->hideDice(); }
					break;
				}

				case QUERY::INFOS_PLAYER_MOVE: {
					GameStateParser game_parser(response);
					PlayerInteractProperty p_i_p = game_parser.parseInteraction();
					int index = this->view->getBoard()->getCellIndex(p_i_p.property_name);
					this->view->getBoard()->unsetPlayer(p_i_p.player);
					this->view->getBoard()->setPlayer(index, p_i_p.player);
					break;
				}

				case QUERY::INFOS_PLAYER_BOUGHT: {
					GameStateParser game_parser(response);
					PlayerInteractProperty p_i_p = game_parser.parseInteraction();
					int index = this->view->getBoard()->getCellIndex(p_i_p.property_name);
					this->view->getBoard()->setPurchased(index, p_i_p.player);
					break;
				}

				case QUERY::USELESS_MESSAGE:{
					break;
				}		

				default: 
					this->view->getConsole()->addText(response);
					break;
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
		this->hideDice();

		if (this->model->isCreator()){
			this->view->getOwnerWaitingText()->addText("Gamecode : " + std::to_string(this->model->getGameCode()));
			this->view->getPlayersWaitingText()->setHidden();
		} else {
			this->view->getPlayersWaitingText()->addText("Gamecode : " + std::to_string(this->model->getGameCode()));
			this->view->getOwnerWaitingText()->setHidden();
		}
	}

	void playerJoinUpdate() { this->view->getInfo()->setPlayersInGame(players_username); }

	void gameStartUpdate(int beginner) {
		if (this->model->getUsername() == players_username[beginner]){
			this->showDice();
		}	
		this->view->getPlayersWaitingText()->setHidden();
		this->view->getOwnerWaitingText()->setHidden();
		
		this->view->getInfo()->clearAllText();
		for (int i = 1; i<= player_nb; i++) {
			this->view->getBoard()->setPlayer(0, i);
			this->view->getInfo()->addPlayer(players_username[i-1]);
			this->view->getInfo()->setMoney(i, 1500);
		}
	}

	void setSubject(Subject* win) { this->win = win; }

};

#endif

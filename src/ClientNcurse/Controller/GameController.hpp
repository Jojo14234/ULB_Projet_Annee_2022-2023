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
			
			switch(cury) {
				case QUERY::INFOS_START: {
					GameLaunchingParser start_parser(response);
					PlayersInformations p_i = start_parser.parseStartInfo();
					player_nb = p_i.player_nb;
					players_username = p_i.player_usernames;
					this->gameStartUpdate(p_i.beginner);
					this->view->getConsole()->addText("La partie commence");
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
					DiceInformations dice_i = game_parser.parseDiceLine();
					if (this->model->isMyTurn()) {
						this->view->getDice1()->setText(std::to_string(dice_i.first_value), 0);
						this->view->getDice2()->setText(std::to_string(dice_i.second_value), 0);
					}  else this->view->getConsole()->addText("Le joueur " + this->model->getPlayerTurn() + " a obtenu " + std::to_string(dice_i.first_value ) + " et " + std::to_string(dice_i.second_value));
					break;
				}

				case QUERY::INFOS_GAME: {
					GameStateParser game_parser(response);
					std::vector<PlayerInformations> players = game_parser.parseEndTurnLine(player_nb);
					for (int i = 0; i < player_nb; i++){
						this->view->getBoard()->movePlayer(players[i].position, i+1);
						for (unsigned int j = 0; j < players[i].properties.size(); j++){
							int index = this->view->getBoard()->getCellIndex(players[i].properties[j].name);
							if (players[i].properties[j].level == 0){
								this->view->getBoard()->setPurchased(index, i+1);
							}
							else this->view->getBoard()->setHouse(index, 2);
						} 
						
						this->view->getInfo()->setPlayerInfo(i+1, players[i].money, players[i].jail_card_nb);
					}
					break;
				}	

				case QUERY::INFOS_NEW_TURN: {
					this->model->setPlayerTurn(response);
					if (response == this->model->getUsername()) { this->view->startTurn(); this->model->startTurn(); }
					else { this->view->endTurn(); this->model->endTurn(); this->view->getConsole()->addText("C'est au tour de " + response + " !"); }
					break;
				}

				case QUERY::INFOS_PLAYER_MOVE: {
					GameStateParser game_parser(response);
					PlayerInteractProperty p_i_p = game_parser.parseInteraction();
					int index = this->view->getBoard()->getCellIndex(p_i_p.property_name);
					this->view->getBoard()->movePlayer(index, p_i_p.player);
					break;
				}

				case QUERY::INFOS_PLAYER_BOUGHT: {
					GameStateParser game_parser(response);
					PlayerInteractProperty p_i_p = game_parser.parseInteraction();
					int index = this->view->getBoard()->getCellIndex(p_i_p.property_name);
					this->view->getBoard()->setPurchased(index, p_i_p.player);
					this->view->getInfo()->changePlayerMoney(p_i_p.player, p_i_p.player_money);
					break;
				}

				case QUERY::INFOS_PLAYER_DIDNT_BUY: {
					if(response != this->model->getUsername()) this->view->getConsole()->addText("Le joueur " + response + " n'a pas achete la propriete");
					break;
				}

				// TODO AJOUTER VISUELLE POUR DIRE QUAND UNE PERSONNE A ACHETÉ UNE MAISON/VENDRE + HOTEL

				case QUERY::INFOS_PLAYER_PAID_PLAYER:{
					GameStateParser game_parser(response);
					PlayerPaidPlayerInformations pppi = game_parser.parsePayement();
					if (this->model->isMyTurn()) {
						this->view->getInfo()->changePlayerMoney(pppi.loser, pppi.loser_money);
						this->view->getInfo()->changePlayerMoney(pppi.winner, pppi.winner_money);
					} else {
						this->view->getConsole()->addText(players_username[pppi.loser-1] + " a paye " + std::to_string(pppi.amount) + " dollars a " + players_username[pppi.winner-1]);
					}
					break;
				}

				case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL:{
					GameStateParser game_parser(response);
					PlayerInteractMortgagedCell pimc = game_parser.parseMortgagedLine();
					this->view->getConsole()->addText(pimc.username + " est tombe sur une propriete hypothequee");
					break;
				}

				case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL:{
					break;
				}

				case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL:{
					GameStateParser game_parser(response);
					PlayerInteractTax pit = game_parser.parseTaxLine();
					this->view->getInfo()->changePlayerMoney(pit.player, pit.player_money);
					this->view->getConsole()->addText(players_username[pit.player] + " a paye " + std::to_string(pit.price) + " dollars de taxe");
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
		this->view->startWaitingRoom();

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
		this->view->endWaitingRoom();
		this->model->setPlayerTurn(players_username[beginner]);
		if (this->model->getUsername() == players_username[beginner]){
			this->view->startTurn();
			this->model->startTurn();
		} 
		
		this->view->getInfo()->clearAllText();
		for (int i = 1; i<= player_nb; i++) {
			this->view->getBoard()->setPlayer(0, i);
			this->view->getInfo()->addPlayerLine(players_username[i-1]);
			this->view->getInfo()->setPlayerInfo(i, 1500, 0);
		}
	}

	void setSubject(Subject* win) { this->win = win; }

};

#endif

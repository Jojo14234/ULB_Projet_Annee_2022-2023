#ifndef _GAME_VIEW_HPP
#define _GAME_VIEW_HPP

#include "AbstractView.hpp"
#include "GameObject/Board.hpp"
#include "Object/InputButtonFrame.hpp"
#include "Object/Text.hpp"
#include "GameObject/Dice.hpp"
#include "GameObject/InformationBox.hpp"
#include "../../utils/AccessMonitor.hpp"


class GameView : public AbstractView {

	int up_margin = 5;
	int left_margin = 8;

	//Creation of the board
	Board board;
	
	//Creation of the dice
	Dice dice1{{3,5,25,60}};
	Dice dice2{{3,5,25,65}};
	
	//Creation of the information box
	Text info_text{ObjectInfo{3, 13, up_margin + 28, 125+((65-13)/2)}, {"Informations"}};
	InformationBox info{{7+(4*2),65,35,125}};

	//Creation of the chat and console
	Text chat_text{ObjectInfo{3, 4, up_margin + 13, 125+((65-4)/2)}, {"Chat"}};
	Text console_text{ObjectInfo{3, 8, up_margin - 2, 125+((65-8)/2)}, {"Console"}};
	InputButtonFrame console{{5+(4*2), 65, up_margin, 125}}; 
	InputButtonFrame chat{{5+(4*2), 65, up_margin + 15, 125}};

	
	Text owner_waiting{{5, 44, up_margin + ((5-1)*(11-1))/2, left_margin + ((11-1)*(11-1)+10-44)/2},
					   {"Vous êtes le propriétaire de cette partie", "Utilisez /start pour lancer la partie"}};
	Text players_waiting{{5, 40, up_margin + ((5-1)*(11-1))/2, left_margin + ((11-1)*(11-1)+10-40)/2},
						 {"En attente du lancement de la partie..."}};
	Text its_your_turn{{3, 18, up_margin-2, 65-18/2}, {"C'est votre tour!"}};

	mutable AccessMonitor am;

public:

	GameView(Client *model, int player_nb) : AbstractView(model), board{{11, 11, up_margin, left_margin}, player_nb} {}
	
	void draw() override {
		this->am.lockWriter();
		board.draw();
		info.draw();
		dice1.draw();
		dice2.draw();

		chat.draw();
		console.draw();
		chat_text.draw();
		console_text.draw();
		info_text.draw();

		players_waiting.draw();
		owner_waiting.draw();
		its_your_turn.draw();
		this->am.unlockWriter();
	}

	Board* getBoard() { return &board; }
	Dice* getDice1() { return &dice1;}
	Dice* getDice2() { return &dice2;}
	InformationBox* getInfo(){return &info;}
	InputButtonFrame* getChat() { return &chat; }
	InputButtonFrame* getConsole() { return &console; }
	Text* getOwnerWaitingText() { return &owner_waiting; }
	Text* getPlayersWaitingText() { return &players_waiting; }
	Text* getItsYourTurnText() { return &its_your_turn; }

	void hideDice(){
		this->clearDice();
		dice1.setHidden();
		dice2.setHidden();
	}

	void showDice(){
		this->clearDice();
		dice1.setVisible();
		dice2.setVisible();
	}

	void clearDice(){
		dice1.clearResult();
		dice2.clearResult();
	}

	void startWaitingRoom(){
		endTurn();
		owner_waiting.setVisible();
		players_waiting.setVisible();
	}

	void endWaitingRoom(){
		owner_waiting.setHidden();
		players_waiting.setHidden();
	}

	void endTurn(){
		this->hideDice();
		its_your_turn.setHidden();
	}

	void startTurn(){
		this->showDice();
		its_your_turn.setVisible();
	}
};

#endif

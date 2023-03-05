#ifndef _GAME_VIEW_HPP
#define _GAME_VIEW_HPP

#include "AbstractView.hpp"
#include "GameObject/Board.hpp"
#include "Object/InputButtonFrame.hpp"
#include "Object/Text.hpp"
#include "GameObject/Dice.hpp"
#include "GameObject/Purse.hpp"
#include "GameObject/InformationBox.hpp"

class GameView : public AbstractView {

	int up_margin = 5;
	int left_margin = 8;

	Board board;
	Dice dice1{{3,5,25,60}};
	Dice dice2{{3,5,25,65}};
	InformationBox storage{{5,62,47,125}};
	Purse purse{6,{9,15,10,80}};

	Text chat_text{ObjectInfo{3, 4, up_margin + 14, 125+((65-4)/2)}, {"chat"}};
	Text console_text{ObjectInfo{3, 8, up_margin - 2, 125+((65-8)/2)}, {"console"}};
	InputButtonFrame console{{5+(4*2), 65, up_margin, 125}}; 
	InputButtonFrame chat{{5+(4*2), 65, up_margin + (4*4), 125}};

	Text owner_waiting{{5, 44, up_margin + ((5-1)*(11-1))/2, left_margin + ((11-1)*(11-1)+10-44)/2},
					   {"Vous êtes le propriétaire de cette partie", "Utilisez /start pour lancer la partie", "Gamecode : "}};
	Text players_waiting{{5, 40, up_margin + ((5-1)*(11-1))/2, left_margin + ((11-1)*(11-1)+10-40)/2},
						 {"En attente du lancement de la partie...", "Gamecode : "}};		   

public:

	GameView(Client *model, int player_nb) : AbstractView(model), board{{11, 11, up_margin, left_margin}, player_nb} {}
	
	void draw() override {
		board.draw();
		storage.draw();
		dice1.draw();
		dice2.draw();
		purse.draw();

		chat.draw();
		console.draw();
		chat_text.draw();
		console_text.draw();

		players_waiting.draw();
		owner_waiting.draw();
	}

	Board* getBoard() { return &board; }
	Dice* getDice1() { return &dice1;}
	Dice* getDice2() { return &dice2;}
	Purse* getPurse() {return &purse;}
	InformationBox* getStorage(){return &storage;}
	InputButtonFrame* getChat() { return &chat; }
	InputButtonFrame* getConsole() { return &console; }
};

#endif

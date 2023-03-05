#ifndef _GAME_VIEW_HPP
#define _GAME_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/Board.hpp"
#include "Object/InputButtonFrame.hpp"
#include "Object/Text.hpp"
#include "Object/Dice.hpp"
#include "Object/Purse.hpp"
#include "Object/JailCardStorage.hpp"

class GameView : public AbstractView {

	int up_margin = 5;
	int left_margin = 8;

	Board board;
	Dice dice1{{3,4,25,60}};
	Dice dice2{{3,4,25,65}};
	JailCardStorage storage{{5,62,47,125}};
	Purse purse{6,{9,15,10,80}};
	Text chat_text{ObjectInfo{3,16, up_margin+ 14, 125+26}, {"chat"}};
	Text console_text{ObjectInfo{3,8, up_margin-2, 125+30}, {"console"}};
	InputButtonFrame console{{5+(4*2), 65, up_margin, 125}}; 
	InputButtonFrame chat{{5+(4*2),65, up_margin + (4*4), 125}};

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
	}

	Board* getBoard() { return &board; }
	Dice* getDice1() { return &dice1;}
	Dice* getDice2() { return &dice2;}
	Purse* getPurse() {return &purse;}
	JailCardStorage* getStorage(){return &storage;}
	InputButtonFrame* getChat() { return &chat; }
	InputButtonFrame* getConsole() { return &console; }
};

#endif

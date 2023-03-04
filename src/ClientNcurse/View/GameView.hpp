#ifndef _GAME_VIEW_HPP
#define _GAME_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/Board.hpp"
#include "Object/InputButtonFrame.hpp"
#include "Object/Text.hpp"


class GameView : public AbstractView {

	int up_margin = 5;
	int left_margin = 8;

	Board board;
	Text chat_text{ObjectInfo{3,16, up_margin+5+(4*4), 125+40-8}, {"chat"}};
	Text console_text{ObjectInfo{3,8, up_margin-2, 125+40-4}, {"console"}};
	InputButtonFrame console{{5+(4*4), 80, up_margin, 125}};
	InputButtonFrame chat{{5+(4*4), 80, up_margin+5+(4*4)+2, 125}};

public:

	GameView(Client *model, int player_nb) : AbstractView(model), board{{11, 11, up_margin, left_margin}, player_nb} {}
	
	void draw() override {
		board.draw();
		chat.draw();
		console.draw();
		chat_text.draw();
		console_text.draw();
	}

	Board* getBoard() { return &board; }
	InputButtonFrame* getChat() { return &chat; }
	InputButtonFrame* getConsole() { return &console; }
};

#endif

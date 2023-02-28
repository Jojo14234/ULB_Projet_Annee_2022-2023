#ifndef _GAME_VIEW_HPP
#define _GAME_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/Board.hpp"


class GameView : public AbstractView {

	Board board;

public:

	GameView(Client *model, int player_nb) : AbstractView(model), board{{1,1,150,150}, player_nb} {}
	
	void draw() override {
		board.draw();
	}
};

#endif

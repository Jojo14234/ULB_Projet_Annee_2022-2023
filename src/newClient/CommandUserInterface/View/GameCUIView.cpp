#include <ncurses.h>

#include "GameCUIView.hpp"


// Public

void GameCUIView::draw() {
    //todo added from n-curse
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

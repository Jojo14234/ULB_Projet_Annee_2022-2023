/**
 * Project Untitled
 */


#include <ncurses.h>

#include "MenuCUIView.hpp"


// Public

MenuCUIView::MenuCUIView() {
	this->error_txt.setHidden();
}

void MenuCUIView::draw() {
	infos_txt.draw();
	commands_txt.draw();
	join_txt.draw();
	join.draw();
	error_txt.draw();
	disconnect.draw();
	console.draw();
}
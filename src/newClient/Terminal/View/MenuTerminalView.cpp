/**
 * Project Untitled
 */


#include <ncurses.h>

#include "MenuTerminalView.hpp"


// Public

MenuTerminalView::MenuTerminalView() {
	this->error_txt.setHidden();
}

void MenuTerminalView::draw() {
	infos_txt.draw();
	commands_txt.draw();
	join_txt.draw();
	join.draw();
	error_txt.draw();
	disconnect.draw();
	console.draw();
}
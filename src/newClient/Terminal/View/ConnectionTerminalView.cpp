/**
 * Project Untitled
 */

#include <ncurses.h>

#include "ConnectionTerminalView.hpp"


// Public

void ConnectionTerminalView::draw() {
	username_input_box.draw();
	password_input_box.draw();
	enter_username.draw();
	enter_password.draw();
	login_button.draw();
	register_button.draw();
}

void ConnectionTerminalView::clear() {
	this->username_input_box.clear();
	this->password_input_box.clear();
	this->username_input_box.reset();
	this->password_input_box.reset();
}
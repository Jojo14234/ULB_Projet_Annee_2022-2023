/**
 * Project Untitled
 */

#include <ncurses.h>

#include "ConnectionCUIView.hpp"


// Public

void ConnectionCUIView::draw() {
	username_input_box.draw();
	password_input_box.draw();
	enter_username.draw();
	enter_password.draw();
	login_button.draw();
	register_button.draw();
}

void ConnectionCUIView::clear() {
	this->username_input_box.clear();
	this->password_input_box.clear();
	this->username_input_box.reset();
	this->password_input_box.reset();
}
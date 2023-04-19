
#include "ConnectionGUIView.hpp"

ConnectionGUIView::ConnectionGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {
		modal_box.addText(new Text{ObjectInfo<>(0, 80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), "Welcome to the game!"});
		modal_box.setHidden();
}

void ConnectionGUIView::draw() {
	logo.draw(*window);
	username_border.draw(*window);
	password_border.draw(*window);
	username.draw(*window);
	password.draw(*window);
	login_button.draw(*window);
	register_button.draw(*window);
	modal_box.draw(*window);
}

void ConnectionGUIView::clear() {
		username.clear();
		password.clear();
}
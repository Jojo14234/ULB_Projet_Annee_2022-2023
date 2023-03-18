#include "WelcomeUIView.hpp"


void WelcomeUIView::draw() {
	background.draw(*this->window);
	logo.draw(*this->window);
}

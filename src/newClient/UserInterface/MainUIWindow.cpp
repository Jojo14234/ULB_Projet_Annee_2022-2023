#include "MainUIWindow.hpp"
#include "configs.hpp"
#include "View/WelcomeUIView.hpp"
#include "View/ConnectionUIView.hpp"
#include "View/MenuUIView.hpp"
#include "View/FriendsUIView.hpp"
#include "View/RankUIView.hpp"
#include "View/GameUIView.hpp"
#include "Controller/WelcomeUIController.hpp"
#include "Controller/ConnectionUIController.hpp"
#include "Controller/MenuUIController.hpp"
#include "Controller/FriendsUIController.hpp"
#include "Controller/RankUIController.hpp"
#include "Controller/GameUIController.hpp"

// Private

void MainUIWindow::initAttributes() {
	// Views
	WelcomeUIView* welcome_view = new WelcomeUIView();
	ConnectionUIView* connection_view = new ConnectionUIView();
	MenuUIView* menu_view = new MenuUIView();
	FriendsUIView* friends_view = new FriendsUIView();
	RankUIView* rank_view = new RankUIView();
	GameUIView* game_view = new GameUIView();
	this->view.setViews({welcome_view, connection_view, menu_view, friends_view, rank_view, game_view});
	// Controllers
	WelcomeUIController* welcome_controller = new WelcomeUIController(&this->model, welcome_view);
	ConnectionUIController* connection_controller = new ConnectionUIController(&this->model, connection_view);
	MenuUIController* menu_controller = new MenuUIController(&this->model, menu_view);
	FriendsUIController* friends_controller = new FriendsUIController(&this->model, friends_view);
	RankUIController* rank_controller = new RankUIController(&this->model, rank_view);
	GameUIController* game_controller = new GameUIController(&this->model, game_view);
	this->controller.setController({welcome_controller, connection_controller, menu_controller, friends_controller, rank_controller, game_controller});
}

void MainUIWindow::draw() {
	this->view.draw(this->state);
	this->window.display();
}


// Public

MainUIWindow::MainUIWindow() :
	window(sf::VideoMode(1500, 1000), "CAPITALI$T") {
	this->initAttributes();
}

MainUIWindow::~MainUIWindow() {
	this->window.close();
}

void MainUIWindow::mainLoop() {
	while (window.isOpen()) {
		sf::Event event;
		this->window.waitEvent(event);
		if (event.type == sf::Event::Closed) break; 
		this->controller.handle(this->state, event);
		this->draw();
	}
}

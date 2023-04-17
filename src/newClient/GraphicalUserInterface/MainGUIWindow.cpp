#include "MainGUIWindow.hpp"
#include "configs.hpp"
#include "View/WelcomeGUIView.hpp"
#include "View/ConnectionGUIView.hpp"
#include "View/MenuGUIView.hpp"
#include "View/FriendsGUIView.hpp"
#include "View/RankGUIView.hpp"
#include "View/GameGUIView.hpp"
#include "Controller/WelcomeGUIController.hpp"
#include "Controller/ConnectionGUIController.hpp"
#include "Controller/MenuGUIController.hpp"
#include "Controller/FriendsGUIController.hpp"
#include "Controller/RankGUIController.hpp"
#include "Controller/GameGUIController.hpp"
#include "View/configs.hpp"


// Private

void MainGUIWindow::initAttributes() {
	// Views
	WelcomeGUIView* welcome_view = new WelcomeGUIView(&this->window);
	ConnectionGUIView* connection_view = new ConnectionGUIView(&this->window);
	MenuGUIView* menu_view = new MenuGUIView(&this->window);
	FriendsGUIView* friends_view = new FriendsGUIView(&this->window);
	RankGUIView* rank_view = new RankGUIView(&this->window);
	GameGUIView* game_view = new GameGUIView(&this->window);
	this->view.setViews({welcome_view, connection_view, menu_view, friends_view, rank_view, game_view});// j'ai suppr game_view qui se trouve juste après rank_view
	// Controllers
	WelcomeGUIController* welcome_controller = new WelcomeGUIController(&this->model, welcome_view);
	ConnectionGUIController* connection_controller = new ConnectionGUIController(&this->model, connection_view);
	MenuGUIController* menu_controller = new MenuGUIController(&this->model, menu_view);
	FriendsGUIController* friends_controller = new FriendsGUIController(&this->model, friends_view);
	RankGUIController* rank_controller = new RankGUIController(&this->model, rank_view);
	GameGUIController* game_controller = new GameGUIController(&this->model, game_view);
  menu_controller->setFriendController(friends_controller);
	this->controller.setController({welcome_controller, connection_controller, menu_controller, friends_controller, rank_controller, game_controller}); // j'ai suppr game_controller qui se trouve juste après rank_controller
}

void MainGUIWindow::draw() {
	this->view.draw(this->state);
	this->window.display();
}

void MainGUIWindow::clear() {
	this->window.clear(BACKGROUND_COLOR);
}

// Public

MainGUIWindow::MainGUIWindow() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CAPITALI$T") {
	this->initAttributes();
}

MainGUIWindow::~MainGUIWindow() {
	this->window.close();
}

void MainGUIWindow::mainLoop() {
	while (window.isOpen()) {
		sf::Event event;
		this->window.waitEvent(event);
		if (event.type == sf::Event::Closed or event.type == sf::Event::KeyPressed
			and event.key.code == sf::Keyboard::Escape ) break;
		this->controller.handle(this->state, event);
		this->clear();
		this->draw();
	}
}

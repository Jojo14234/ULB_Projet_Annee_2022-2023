#include <ncurses.h>

#include "MainCUIWindow.hpp"
#include "configs.hpp"
#include "View/ConnectionCUIView.hpp"
#include "View/MenuCUIView.hpp"
#include "View/GameCUIView.hpp"
#include "Controller/ConnectionCUIController.hpp"
#include "Controller/MenuCUIController.hpp"
#include "Controller/GameCUIController.hpp"

// Private

void MainCUIWindow::initAttributes() {
	// Views
	ConnectionCUIView* connection_view = new ConnectionCUIView();
	MenuCUIView* menu_view = new MenuCUIView();
	GameCUIView* game_view = new GameCUIView(6);
	this->view.setViews({connection_view, menu_view, game_view});
	// Controllers
	ConnectionCUIController* connection_controller = new ConnectionCUIController(&this->model, connection_view);
	GameCUIController* game_controller = new GameCUIController(&this->model, game_view);
	MenuCUIController* menu_controller = new MenuCUIController(&this->model, menu_view, game_controller);
	this->controller.setController({connection_controller, menu_controller, game_controller});
}

void MainCUIWindow::draw() {
	this->window.draw();
	this->view.draw(state);
	refresh();
}


// Public

MainCUIWindow::MainCUIWindow() {
	cbreak();	// Line buffering disabled, Pass on everything to me
	noecho();	// Don't echo() while we do getch
	keypad(stdscr, TRUE);	// I need that nifty F
	mousemask(ALL_MOUSE_EVENTS, NULL);	// To get all mouse events
	refresh();	// Print it on to the real screen
	this->initAttributes();
	this->draw();
	this->controller.move(state);
}

MainCUIWindow::~MainCUIWindow() {
	endwin();	// End curses mode
}

void MainCUIWindow::mainLoop() {
	int event;
	while ( (event=getch()) ) {
		if ( event == 27 ) break;	// ESC
		this->controller.handle(state, event);
		this->draw();
		this->controller.move(state);
	}
}

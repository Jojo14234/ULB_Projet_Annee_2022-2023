#include <ncurses.h>

#include "MainTerminalWindow.hpp"
#include "configs.hpp"
#include "View/ConnectionTerminalView.hpp"
#include "View/MenuTerminalView.hpp"
#include "View/GameTerminalView.hpp"
#include "Controller/ConnectionTerminalController.hpp"
#include "Controller/MenuTerminalController.hpp"
#include "Controller/GameTerminalController.hpp"

// Private

void MainTerminalWindow::initAttributes() {
	// Views
	ConnectionTerminalView* connection_view = new ConnectionTerminalView();
	MenuTerminalView* menu_view = new MenuTerminalView();
	GameTerminalView* game_view = new GameTerminalView();
	this->view = MainView<STATE>{connection_view, menu_view, game_view};
	// Controllers
	ConnectionTerminalController* connection_controller = new ConnectionTerminalController(&this->model, connection_view);
	MenuTerminalController* menu_controller = new MenuTerminalController(&this->model, menu_view);
	GameTerminalController* game_controller = new GameTerminalController(&this->model, game_view);
	this->controller = MainController<STATE, int>{connection_controller, menu_controller, game_controller};
}

void MainTerminalWindow::draw() {
	//this->window.draw();
	this->view.draw(state);
	refresh();
}


// Public

MainTerminalWindow::MainTerminalWindow() {
	cbreak();	// Line buffering disabled, Pass on everything to me
	noecho();	// Don't echo() while we do getch
	keypad(stdscr, TRUE);	// I need that nifty F
	mousemask(ALL_MOUSE_EVENTS, NULL);	// To get all mouse events
	refresh();	// Print it on to the real screen
	endwin();
	this->initAttributes();
}

MainTerminalWindow::~MainTerminalWindow() {
	endwin();	// End curses mode
}

void MainTerminalWindow::mainLoop() {
	this->draw();
	exit(0);
	this->controller.move(state);
	int event;
	while ( (event=getch()) ) {
		if ( event == 27 ) break;	// ESC
		this->controller.handle(state, event);
		endwin();
		exit(0);
		this->draw();
		this->controller.move(state);
	}
}

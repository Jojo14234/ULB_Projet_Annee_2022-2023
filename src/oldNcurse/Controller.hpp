#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <ncurses.h>
#include <iostream>
#include <string>


enum class STATE { CONNECTION, MENU, GAME };


class MainView {

	ConnectionView connection_view;
	MenuView menu_view;
	GameView game_view;
	
public:

	MainView();

	void draw(STATE state);

};


class MainModel {

	ConnectionModel connection_model;
	MenuModel menu_model;
	GameModel game_model;

public:
	
	MainModel();

	void update(STATE state);

};


class Controller {
	
	MainView view;
	MainModel model;


public:

	Controller();

};

#endif

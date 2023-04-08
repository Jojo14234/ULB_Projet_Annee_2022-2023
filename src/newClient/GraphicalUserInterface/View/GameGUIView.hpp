/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


#include "GameObject/Board.hpp"
#include "GameObject/ActionBox.hpp"
#include "GameObject/InfoBox.hpp"



class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {
	Board board;
	ActionBox actionBox;
	InfoBox infoBox;
	std::vector<std::string> act {"hypo","vendre","constru","dice","babaa"};  //pour tester , à enlever
	std::vector<std::string> colorlist{"red","blue","green","cyan","magenta","yellow"};   //pour tester à enlever
	// Objects

public:

	explicit GameGUIView(sf::RenderWindow* window) : AbstractGUIView(window)
	,board{}
	,actionBox{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red }
	,infoBox{ObjectInfo<>(400, 400,window->getSize().x -400,window->getSize().y - 350)}
	{
		 actionBox.setButton(act,24);
		 infoBox.initMoney(colorlist,300000);
		 infoBox.setMoney(4,520);
	}

	
	~GameGUIView()=default;

	void draw() override {
		board.draw(*window);
		actionBox.draw(*window);
		infoBox.draw(*window);
	}

	void clear();

	friend class GameGUIController;
	//Board* getBoard() { return &board; }

};
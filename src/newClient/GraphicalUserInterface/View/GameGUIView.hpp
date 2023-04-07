/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


#include "GameObject/Board.hpp"
#include "GameObject/ActionBox.hpp"
//#include "GameObject/InfoBox.hpp"



class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {
	Board board;
	ActionBox actionBox;
	std::vector<std::string> act {"hypo","vendre","constru","dice","babaa"};  //pour tester , à enlever
	// Objects

public:

	explicit GameGUIView(sf::RenderWindow* window) : AbstractGUIView(window)
	,board{}
	,actionBox{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red }
	{
		 //actionBox.setButton(act,24);
	}

	
	~GameGUIView()=default;

	void draw() override {
		//board.draw(*window);
		actionBox.draw(*window);
	}

	void clear();

	friend class GameGUIController;
	//Board* getBoard() { return &board; }

};
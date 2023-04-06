/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


#include "GameObject/Board.hpp"
//#include "GameObject/ActionBox.hpp"
//#include "GameObject/InfoBox.hpp"



class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {
	Board board;
	// Objects

public:

	explicit GameGUIView(sf::RenderWindow* window, int player_nb) : AbstractGUIView(window)
	,board{sf::Vector2f{100,80},sf::Vector2f{100,100}, player_nb}
	{
		
	}

	
	~GameGUIView()=default;

	void draw() override {
		board.draw(*window);
	}

	void clear();

	friend class GameGUIController;

};
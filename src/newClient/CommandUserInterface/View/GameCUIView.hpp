/**
 * Project Untitled
 */

#pragma once

#include <ncurses.h>

#include "AbstractCUIView.hpp"
#include "Objects.hpp"


class GameCUIController; // forward declaration

class GameCUIView: public AbstractCUIView {

	// Objects

public: 
	
	GameCUIView()=default;
	
	~GameCUIView()=default;

	void draw() override;

	friend class GameCUIController;

};
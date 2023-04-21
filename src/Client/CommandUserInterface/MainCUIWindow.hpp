/**
 * Project Untitled
 */

#pragma once

#include <ncurses.h>

#include "../AbstractMainWindow.hpp"
#include "AbstractCUI.hpp"
#include "configs.hpp"
#include "View/Objects.hpp"


class MainCUIWindow: public AbstractMainWindow<STATE, int>, public AbstractCUI {

	Window window{ObjectInfo{LINES, COLS, 0, 0}, "CAPITALI$T"};


	void initAttributes() override;
	
	void draw() override;

public:
	
	MainCUIWindow();
	
	~MainCUIWindow();
	
	void mainLoop() override;

};
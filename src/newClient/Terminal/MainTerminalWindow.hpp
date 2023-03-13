/**
 * Project Untitled
 */

#pragma once

#include <ncurses.h>

#include "../AbstractMainWindow.hpp"
#include "AbstractTerminal.hpp"
#include "configs.hpp"
#include "View/Objects.hpp"


class MainTerminalWindow: public AbstractMainWindow<STATE, int>, public AbstractTerminal {

	Window window{ObjectInfo{LINES, COLS, 0, 0}, "CAPITALI$T"};


	void initAttributes() override;
	
	void draw() override;

public:
	
	MainTerminalWindow();
	
	~MainTerminalWindow();
	
	void mainLoop() override;

};
/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalView.hpp"
#include "Objects.hpp"


class GameTerminalController; // forward declaration

class GameTerminalView: public AbstractTerminalView {

	// Objects

public: 
	
	GameTerminalView()=default;
	
	~GameTerminalView()=default;

	void draw() override;

	friend class GameTerminalController;

};
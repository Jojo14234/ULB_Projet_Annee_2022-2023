/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalView.hpp"
#include "Objects.hpp"


class MenuTerminalController; // forward declaration

class MenuTerminalView: public AbstractTerminalView {

	// Objects

public: 
	
	MenuTerminalView()=default;
	
	~MenuTerminalView()=default;

	void draw() override;

	void clear();

	friend class MenuTerminalController;

};
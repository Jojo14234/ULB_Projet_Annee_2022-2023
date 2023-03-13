/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalView.hpp"
#include "Objects.hpp"


class ConnectionTerminalController; // forward declaration

class ConnectionTerminalView: public AbstractTerminalView {

	// Objects

public: 
	
	ConnectionTerminalView()=default;
	
	~ConnectionTerminalView()=default;

	void draw() override;

	void clear();

	friend class ConnectionTerminalController;

};
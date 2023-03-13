/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class ConnectionUIController; // forward declaration

class ConnectionUIView: public AbstractUIView {

	// Objects

public: 
	
	ConnectionUIView()=default;
	
	~ConnectionUIView()=default;

	void draw() override;

	void clear();

	friend class ConnectionUIController;

};
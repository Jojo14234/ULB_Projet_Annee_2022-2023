/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class MenuUIController; // forward declaration

class MenuUIView: public AbstractUIView {

	// Objects

public: 
	
	MenuUIView()=default;
	
	~MenuUIView()=default;

	void draw() override;

	friend class MenuUIController;

};
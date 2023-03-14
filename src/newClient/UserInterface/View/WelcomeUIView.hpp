/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class WelcomeUIController; // forward declaration

class WelcomeUIView: public AbstractUIView {

	// Objects

public: 
	
	WelcomeUIView()=default;
	
	~WelcomeUIView()=default;

	void draw() override;

	friend class WelcomeUIController;

};
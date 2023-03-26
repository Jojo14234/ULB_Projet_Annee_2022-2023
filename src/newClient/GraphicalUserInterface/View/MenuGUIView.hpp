/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


class MenuGUIController; // forward declaration

class MenuGUIView: public AbstractGUIView {

	// Objects

public:

	using AbstractGUIView::AbstractGUIView;
	
	~MenuGUIView()=default;

	void draw() override {}

	friend class MenuGUIController;

};
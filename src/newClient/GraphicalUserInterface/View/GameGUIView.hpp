/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {

	// Objects

public:

	using AbstractGUIView::AbstractGUIView;
	
	~GameGUIView()=default;

	void draw() override {}

	void clear();

	friend class GameGUIController;

};
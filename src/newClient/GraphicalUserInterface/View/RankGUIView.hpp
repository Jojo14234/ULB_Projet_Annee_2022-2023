/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


class RankGUIController; // forward declaration

class RankGUIView: public AbstractGUIView {

	// Objects

public:

	using AbstractGUIView::AbstractGUIView;
	
	~RankGUIView()=default;

	void draw() override {}

	friend class RankGUIController;

};
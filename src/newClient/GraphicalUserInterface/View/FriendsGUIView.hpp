/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


class FriendsGUIController; // forward declaration

class FriendsGUIView: public AbstractGUIView {

	// Objects

public:

	using AbstractGUIView::AbstractGUIView;
	
	~FriendsGUIView()=default;

	void draw() override {}

	void clear();

	friend class FriendsGUIController;

};
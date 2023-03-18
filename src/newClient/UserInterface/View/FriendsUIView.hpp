/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class FriendsUIController; // forward declaration

class FriendsUIView: public AbstractUIView {

	// Objects

public:

	using AbstractUIView::AbstractUIView;
	
	~FriendsUIView()=default;

	void draw() override;

	void clear();

	friend class FriendsUIController;

};
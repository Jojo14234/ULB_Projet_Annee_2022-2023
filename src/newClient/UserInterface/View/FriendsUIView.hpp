/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class FriendsUIController; // forward declaration

class FriendsUIView: public AbstractUIView {

	// Objects

public: 
	
	FriendsUIView()=default;
	
	~FriendsUIView()=default;

	void draw() override;

	void clear();

	friend class FriendsUIController;

};
/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class RankUIController; // forward declaration

class RankUIView: public AbstractUIView {

	// Objects

public: 
	
	RankUIView()=default;
	
	~RankUIView()=default;

	void draw() override;

	friend class RankUIController;

};
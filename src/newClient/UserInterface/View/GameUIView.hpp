/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"


class GameUIController; // forward declaration

class GameUIView: public AbstractUIView {

	// Objects

public:

	using AbstractUIView::AbstractUIView;
	
	~GameUIView()=default;

	void draw() override;

	void clear();

	friend class GameUIController;

};
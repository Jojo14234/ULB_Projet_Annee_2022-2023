/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"
#include "Objects.hpp"
#include "ImagesPath.hpp"


class ConnectionUIController; // forward declaration

class ConnectionUIView: public AbstractUIView {

	// Objects

public:

	using AbstractUIView::AbstractUIView;
	
	~ConnectionUIView()=default;

	void draw() override;

	void clear();

	friend class ConnectionUIController;

};
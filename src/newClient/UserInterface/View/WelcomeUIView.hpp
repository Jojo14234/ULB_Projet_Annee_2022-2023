/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"
#include "Objects.hpp"
#include "ImagesPath.hpp"


class WelcomeUIController; // forward declaration

class WelcomeUIView: public AbstractUIView {

	// Objects
	Image logo{ObjectInfo<>(788.f, 145.f, WINDOW_WIDTH/2.f - 788.f/2.f, WINDOW_HEIGHT/10.f), LOGO_PATH};

public:

	using AbstractUIView::AbstractUIView;
	
	~WelcomeUIView()=default;

	void draw() override;

	friend class WelcomeUIController;

};
/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"


class WelcomeUIController; // forward declaration

class WelcomeUIView: public AbstractUIView {

	// Objects
	Image logo{ObjectInfo<>(788.f, 145.f, WINDOW_WIDTH/2.f - 788.f/2.f, WINDOW_HEIGHT/10.f), LOGO_PATH};
	Box background{ObjectInfo<>(WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 0.f), sf::Color(98, 205, 255)};
	Text title{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT*9/10.f, 0.f, WINDOW_HEIGHT/10.f), "YOUHOU", ARIAL_FONT_PATH};

public:

	using AbstractUIView::AbstractUIView;
	
	~WelcomeUIView()=default;

	void draw() override;

	friend class WelcomeUIController;

};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "../../View/AbstractView.hpp"
#include "../AbstractUI.hpp"
#include "../configs.hpp"


class AbstractUIView: public AbstractView, public AbstractUI {

protected:

	sf::RenderWindow* window;

public:
	
	explicit AbstractUIView(sf::RenderWindow* window) : window(window) {}

	virtual ~AbstractUIView()=default;

	virtual void draw()=0;

};
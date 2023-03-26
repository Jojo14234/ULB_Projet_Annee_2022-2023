/**
 * Project Untitled
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "../../View/AbstractView.hpp"
#include "../AbstractGUI.hpp"
#include "../configs.hpp"


class AbstractGUIView: public AbstractView, public AbstractGUI {

protected:

	sf::RenderWindow* window;

public:
	
	explicit AbstractGUIView(sf::RenderWindow* window) : window(window) {}

	virtual ~AbstractGUIView()=default;

	virtual void draw()=0;

};
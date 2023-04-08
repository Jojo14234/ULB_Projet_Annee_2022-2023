/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class RankGUIView; // forward declaration

class RankGUIController: public AbstractGUIController {

	RankGUIView* view;

public: 
	
	RankGUIController(Client* model, RankGUIView* view) : AbstractGUIController(model, STATE::RANK), view{view} {}

	~RankGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
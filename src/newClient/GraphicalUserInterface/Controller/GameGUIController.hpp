/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class GameGUIView; // forward declaration

class GameGUIController: public AbstractGUIController {


	GameGUIView* view;

public: 
	
	GameGUIController(Client* model, GameGUIView* view) : AbstractGUIController(model, STATE::GAME), view{view} {}

	~GameGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
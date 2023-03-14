/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class GameUIView; // forward declaration

class GameUIController: public AbstractUIController {


	GameUIView* view;

public: 
	
	GameUIController(Client* model, GameUIView* view) : AbstractUIController(model, STATE::GAME), view{view} {}

	~GameUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class CreateGameGUIView; // forward declaration

class CreateGameGUIController: public AbstractGUIController {


	CreateGameGUIView* view;

public: 
	
	CreateGameGUIController(Client* model, CreateGameGUIView* view) : AbstractGUIController(model, STATE::CREATE), view{view} {}

	~CreateGameGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class SettingsGUIView; // forward declaration

class SettingsGUIController: public AbstractGUIController {


	SettingsGUIView* view;

public: 
	
	SettingsGUIController(Client* model, SettingsGUIView* view) : AbstractGUIController(model, STATE::SETTINGS), view{view} {}

	~SettingsGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
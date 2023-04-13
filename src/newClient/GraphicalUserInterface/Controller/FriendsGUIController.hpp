/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "SubjectGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class FriendsGUIView; // forward declaration

class FriendsGUIController: public AbstractGUIController, public SubjectGUIController {

	FriendsGUIView* view;

public: 
	
	FriendsGUIController(Client* model, FriendsGUIView* view) : AbstractGUIController(model, STATE::FRIENDS), view(view) {}

	~FriendsGUIController()=default;

	void handle(sf::Event event) override;

	void update() override;

	// ...

};
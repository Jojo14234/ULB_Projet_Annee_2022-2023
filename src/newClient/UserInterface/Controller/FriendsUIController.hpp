/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class FriendsUIView; // forward declaration

class FriendsUIController: public AbstractUIController {


	FriendsUIView* view;

public: 
	
	FriendsUIView(Client* model, FriendsUIView* view) : AbstractUIController(model, STATE::FRIENDS), view(view) {}

	~FriendsUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
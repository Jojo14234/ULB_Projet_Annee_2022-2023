/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class RankUIView; // forward declaration

class RankUIController: public AbstractUIController {


	RankUIView* view;

public: 
	
	RankUIView(Client* model, RankUIView* view) : AbstractUIController(model, STATE::Rank), view{view} {}

	~RankUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
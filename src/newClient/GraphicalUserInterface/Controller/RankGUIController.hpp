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

	enum RANK_STATE { TOP, MY_RANK };
	RANK_STATE state = TOP;


	RankGUIView* view;

public: 
	
	RankGUIController(Client* model, RankGUIView* view) : AbstractGUIController(model, STATE::RANK), view{view} {}

	~RankGUIController()=default;

	void handle(sf::Event event) override;

	// ...

};
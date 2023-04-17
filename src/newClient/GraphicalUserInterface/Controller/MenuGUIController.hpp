/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "SubjectGUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class MenuGUIView; // forward declaration

class MenuGUIController: public AbstractGUIController {

	MenuGUIView* view;
	SubjectGUIController* friend_controller;

public: 
	
	MenuGUIController(Client* model, MenuGUIView* view) : AbstractGUIController(model, STATE::MENU), view{view} {}

	~MenuGUIController()=default;

	void handle(sf::Event event) override;

	// SETTERS
	void setFriendController(SubjectGUIController* friend_controller) { this->friend_controller = friend_controller; }
	
	// ...

    bool doSettingBtnNContain(int n, sf::Event event);
    bool doSettingBtnNContain(int n, sf::Event event, bool right_side);

    bool doCreatePopUpBtnNContain(int n, sf::Event event);
    bool doCreatePoUpSelectorNContain(int n, sf::Event event, bool right_side);

    bool doJoinPopUpNBtnContain(int n, sf::Event event);

    void createPopUpClick(int n, bool right_side);
    void settingPopUpClick(int n, bool right_side);

    void createProcess();
};
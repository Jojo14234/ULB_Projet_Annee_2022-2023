/**
 * Project Untitled
 */

#pragma once

#include <ncurses.h>

#include "AbstractCUIView.hpp"
#include "Objects.hpp"


class ConnectionCUIController; // forward declaration

class ConnectionCUIView: public AbstractCUIView {

	InputBox username_input_box{ObjectInfo{3, 20, 4, (COLS-20)/2}};
	HiddenInputBox password_input_box{ObjectInfo{3, 20, 9, (COLS-20)/2}};

	Text enter_username{ObjectInfo{3, 20, 2, (COLS-20)/2}, {"Nom d'utilisateur:"}};
	Text enter_password{ObjectInfo{3, 20, 7, (COLS-20)/2}, {"   Mot de passe:"}};

	TextButton login_button{ObjectInfo{3, 20, 13, COLS/2 - 20 -2 }, {"Se connecter"}};
	TextButton register_button{ObjectInfo{3, 20, 13, COLS/2 + 2}, {"Creer un compte"}};

public: 
	
	ConnectionCUIView()=default;
	
	~ConnectionCUIView()=default;

	void draw() override;

	void clear();

	friend class ConnectionCUIController;

};
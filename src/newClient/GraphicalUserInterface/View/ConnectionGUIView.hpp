/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"


class ConnectionGUIController; // forward declaration

class ConnectionGUIView: public AbstractGUIView {

	// Objects
	Image logo{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_WIDTH/2.f * 145.f/788.f, WINDOW_WIDTH/4.f , WINDOW_HEIGHT/10.f), LOGO_PATH};

	InputBox username{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/10.f), BOX_COLOR, SERIF_FONT_PATH};
	InputBox password{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2.f), BOX_COLOR, SERIF_FONT_PATH};
	Border username_border{username, 5};
	Border password_border{password, 5};

	ImageButton login_button{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 230.f/839.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/4.f - WINDOW_WIDTH/100.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/5.f), LOGIN_BUTTON_PATH};
	ImageButton register_button{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 230.f/839.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/100.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/5.f), REGISTER_BUTTON_PATH};

	ModalBox modal_box{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};


public:

	explicit ConnectionGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {
		modal_box.addText(new Text{ObjectInfo<>(0, 80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), "Welcome to the game!"});
		modal_box.setHidden();
	}

	~ConnectionGUIView()=default;

	void draw() override {
		logo.draw(*window);
		username_border.draw(*window);
		password_border.draw(*window);
		username.draw(*window);
		password.draw(*window);
		login_button.draw(*window);
		register_button.draw(*window);
		modal_box.draw(*window);
	}

	void clear();

	friend class ConnectionGUIController;

};
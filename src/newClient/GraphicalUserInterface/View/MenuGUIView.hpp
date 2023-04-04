/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"


class MenuGUIController; // forward declaration

class MenuGUIView: public AbstractGUIView {

	// Objects

	TextButton quit_button{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/12.f, WINDOW_WIDTH/3-75.f, WINDOW_HEIGHT/5*4.f), ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/6*5-15.f), "QUITtER", BLACK, WHITE};
	Border quit_border {quit_button, 3, BLACK};

	ImageButton join{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f,WINDOW_HEIGHT/8.f),JOIN_BUTTON_PATH};
	ImageButton create{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f,WINDOW_HEIGHT/8.f),CREATE_BUTTON_PATH};

	ImageButton rank{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+WINDOW_WIDTH/4.f,WINDOW_HEIGHT/8.f),RANK_BUTTON_PATH};
	ImageButton friend_menu{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+(WINDOW_WIDTH/4*2.f),WINDOW_HEIGHT/8.f),FRIEND_MENU_BUTTON_PATH};

	ImageButton settings{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+(WINDOW_WIDTH/4*3.f),WINDOW_HEIGHT/8.f),SETTINGS_BUTTON_PATH};

public:

	using AbstractGUIView::AbstractGUIView;
	
	~MenuGUIView()=default;

	void draw() override {
		//bordure draw puis box draw
		quit_border.draw(*window);
		quit_button.draw(*window);

		join.draw(*window);
		rank.draw(*window);
		friend_menu.draw(*window);
		settings.draw(*window);
	}

	friend class MenuGUIController;

};
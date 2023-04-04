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

	TextButton quit_button{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/12.f, WINDOW_WIDTH/4, WINDOW_HEIGHT/6*5), ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50,WINDOW_WIDTH/2, WINDOW_HEIGHT/6*5+15), "QUITtER", BLACK, WHITE};
	Border quit_border {quit_button, 3, BLACK};

	ImageButton join{ObjectInfo<>(WINDOW_WIDTH/5,WINDOW_HEIGHT/2,WINDOW_WIDTH/15,WINDOW_HEIGHT/10),JOIN_BUTTON_PATH};
	ImageButton create{ObjectInfo<>(WINDOW_WIDTH/5,WINDOW_HEIGHT/2,100,WINDOW_HEIGHT/10),CREATE_BUTTON_PATH};

	ImageButton rank{ObjectInfo<>(WINDOW_WIDTH/5,WINDOW_HEIGHT/2,WINDOW_WIDTH/15+WINDOW_WIDTH/4,WINDOW_HEIGHT/10),RANK_BUTTON_PATH};

	ImageButton friend_menu{ObjectInfo<>(WINDOW_WIDTH/5,WINDOW_HEIGHT/2,WINDOW_WIDTH/15+(WINDOW_WIDTH/4*2),WINDOW_HEIGHT/10),FRIEND_MENU_BUTTON_PATH};

	ImageButton settings{ObjectInfo<>(WINDOW_WIDTH/5,WINDOW_HEIGHT/2,WINDOW_WIDTH/15+(WINDOW_WIDTH/4*3),WINDOW_HEIGHT/10),SETTINGS_BUTTON_PATH};

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
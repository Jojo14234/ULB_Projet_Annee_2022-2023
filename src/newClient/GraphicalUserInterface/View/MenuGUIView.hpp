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

	Image play{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f-WINDOW_HEIGHT/12,WINDOW_WIDTH/20.f,WINDOW_HEIGHT/8.f), PLAY_IMAGE_PATH};
	ImageButton join{ObjectInfo<>(WINDOW_WIDTH/5.f/2,WINDOW_HEIGHT/12.f,WINDOW_WIDTH/20.f,WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/2.f-WINDOW_HEIGHT/12),JOIN_BUTTON_PATH};
	ImageButton create{ObjectInfo<>(WINDOW_WIDTH/5.f/2,WINDOW_HEIGHT/12.f,WINDOW_WIDTH/20.f+WINDOW_WIDTH/5.f/2,WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/2.f-WINDOW_HEIGHT/12),CREATE_BUTTON_PATH};
	ModalBox create_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2+WINDOW_HEIGHT/3.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6.f), BOX_COLOR};
	ModalBox join_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

	ImageButton rank{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+WINDOW_WIDTH/4.f,WINDOW_HEIGHT/8.f),RANK_BUTTON_PATH};
	ImageButton friend_menu{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+(WINDOW_WIDTH/4*2.f),WINDOW_HEIGHT/8.f),FRIEND_MENU_BUTTON_PATH};

	ImageButton settings{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+(WINDOW_WIDTH/4*3.f),WINDOW_HEIGHT/8.f),SETTINGS_BUTTON_PATH};
	ModalBox settings_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

public:

	explicit MenuGUIView(sf::RenderWindow* window);
	
	~MenuGUIView()=default;

	void initSettingsPopup();
	void initCreatePopup();
	void initJoinPopup();

	void draw() override;

	std::string getCreateCmd();

	friend class MenuGUIController;

};
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
	ModalBox create_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

	ImageButton rank{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+WINDOW_WIDTH/4.f,WINDOW_HEIGHT/8.f),RANK_BUTTON_PATH};
	ImageButton friend_menu{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+(WINDOW_WIDTH/4*2.f),WINDOW_HEIGHT/8.f),FRIEND_MENU_BUTTON_PATH};

	ImageButton settings{ObjectInfo<>(WINDOW_WIDTH/5.f,WINDOW_HEIGHT/2.f,WINDOW_WIDTH/20.f+(WINDOW_WIDTH/4*3.f),WINDOW_HEIGHT/8.f),SETTINGS_BUTTON_PATH};
	ModalBox settings_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

public:

	explicit MenuGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {
		settings_popup.setHidden();
		settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/4.f), "Réglages :D"});
		settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "Taille de fenêtre:"});
		settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), "Son:"});
		settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), "Supprimer son compte:"});
		settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
		settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/25.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), OK_BUTTON_PATH});
		settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH});
		settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), LEFT_BUTTON_PATH});
		settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "1600 x 900"});
		settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/30.f, WINDOW_HEIGHT/30.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - 100 , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), YES_BUTTON_PATH});

		create_popup.setHidden();
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/4.f), "Créer une partie :D"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "Nombre de joueur:"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), "Mode:"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), "Chrono:"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*4.f), "Durée enchère:"});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/25.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), OK_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), LEFT_BUTTON_PATH});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "4"});

		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), RIGHT_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*2), LEFT_BUTTON_PATH});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*2), "Mode classique"});

		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), RIGHT_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*3), LEFT_BUTTON_PATH});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*3), "30 sec"});

		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*4.f), RIGHT_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*4), LEFT_BUTTON_PATH});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*4), "15 sec"});
	}
	
	~MenuGUIView()=default;

	void draw() override {
		//bordure draw puis box draw
		quit_border.draw(*window);
		quit_button.draw(*window);
		join.draw(*window);
		create.draw(*window);
		rank.draw(*window);
		friend_menu.draw(*window);
		settings.draw(*window);
		settings_popup.draw(*window);
		create_popup.draw(*window);
	}

	friend class MenuGUIController;

};
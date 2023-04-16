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
	ModalBox create_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};
	ModalBox join_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

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
		std::vector<std::string> window_sizes{"1600 x 900", "1920 x 1080", "2560 x 1600"};
		DirectionImButton* l_button= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), LEFT_BUTTON_PATH};
		DirectionImButton* r_button= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH};
		std::vector<DirectionImButton*> buttons_selector{l_button, r_button};
		settings_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), window_sizes, buttons_selector});
		settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/30.f, WINDOW_HEIGHT/30.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - 100 , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), YES_BUTTON_PATH});

		create_popup.setHidden();
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/4.f), "Créer une partie :D"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "Nombre de joueur:"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), "Mode:"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), "Chrono:"});
		create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*4.f), "Durée enchère:"});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
		create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/25.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), OK_BUTTON_PATH});

		std::vector<std::string> player_nbr{"2", "3", "4", "5", "6"};
		DirectionImButton* l_button1= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH};
		DirectionImButton* r_button1= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), LEFT_BUTTON_PATH};
		std::vector<DirectionImButton*> buttons_selector1{l_button1, r_button1};
		create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), player_nbr, buttons_selector1});


		std::vector<std::string> game_mode{"Mode classique", "Mode rapide"};
		DirectionImButton* l_button2= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), RIGHT_BUTTON_PATH};
		DirectionImButton* r_button2= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*2), LEFT_BUTTON_PATH};
		std::vector<DirectionImButton*> buttons_selector2{l_button2, r_button2};
		create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*2), game_mode, buttons_selector2});


		std::vector<std::string> chrono{"30s", "45s"};
		DirectionImButton* l_button3= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), RIGHT_BUTTON_PATH};
		DirectionImButton* r_button3= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*3), LEFT_BUTTON_PATH};
		std::vector<DirectionImButton*> buttons_selector3{l_button3, r_button3};
		create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*3), chrono, buttons_selector3});


		std::vector<std::string> auction{"15s", "20s"};
		DirectionImButton* l_button4= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*4.f), RIGHT_BUTTON_PATH};
		DirectionImButton* r_button4= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*4), LEFT_BUTTON_PATH};
		std::vector<DirectionImButton*> buttons_selector4{l_button4, r_button4};
		create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*4), auction, buttons_selector4});

		join_popup.setHidden();
		join_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4.f), "Rejoindre une partie :D"});
		join_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4+100.f), "Entrez le code de jeu"});
		join_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
		join_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/2, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f), OK_BUTTON_PATH});
		join_popup.addInput(new InputBox{ObjectInfo<>(WINDOW_WIDTH/8, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f-WINDOW_WIDTH/4, WINDOW_HEIGHT/2),BOX_COLOR, SERIF_FONT_PATH});
	}
	
	~MenuGUIView()=default;

	void draw() override {
		//bordure draw puis box draw
		quit_border.draw(*window);
		quit_button.draw(*window);
		play.draw(*window);
		join.draw(*window);
		create.draw(*window);
		rank.draw(*window);
		friend_menu.draw(*window);
		settings.draw(*window);
		settings_popup.draw(*window);
		create_popup.draw(*window);
		join_popup.draw(*window);
	}

	std::string getCreateCmd() {
		// /create [mode] [startMoney] [MaxPlayer] [MaxHome]
		std::string cmd = "/create";
		std::vector<std::string> game_parameters;
		const std::vector<std::unique_ptr<Selector>>& selectors = create_popup.getAllSelectors();
		for (const auto& selector : selectors) {
			game_parameters.push_back(selector->getActualString());
		}
		// mode
		std::string mode = game_parameters.at(1) == "Mode classique" ? "normal" : "fast";
		std::string start_money = "1500";
		std::string max_player = game_parameters.at(0);

		return cmd;

	}

	friend class MenuGUIController;

};
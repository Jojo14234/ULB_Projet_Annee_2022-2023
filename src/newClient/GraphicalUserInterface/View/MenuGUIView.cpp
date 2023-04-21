#include "MenuGUIView.hpp"

MenuGUIView::MenuGUIView(sf::RenderWindow* window) : AbstractGUIView(window){
	this->initSettingsPopup();
	this->initCreatePopup();
	this->initJoinPopup();
}

void MenuGUIView::initSettingsPopup(){
	settings_popup.setHidden();
	settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/4.f), "Reglages :D"});
	settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "Taille de fenetre:"});
	settings_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), "Son:"});
	//settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/10.f, WINDOW_HEIGHT/10.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
    settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
    //settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/10.f, WINDOW_HEIGHT/10.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/25.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), OK_BUTTON_PATH});
    settings_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/25.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), OK_BUTTON_PATH});

    std::vector<std::string> window_sizes{"1600 x 900", "1920 x 1080", "2560 x 1600"};
	DirectionImButton* l_button= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), LEFT_BUTTON_PATH};
	DirectionImButton* r_button= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector{l_button, r_button};
	settings_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), window_sizes, buttons_selector});

	std::vector<std::string> sound_volume{{ "Pas de son :(","Petit son","Petit moyen son","Moyen son", "Grand moyen son", "Gros son"}};
	DirectionImButton* l_button2= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*2), LEFT_BUTTON_PATH};
	DirectionImButton* r_button2= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f*2), RIGHT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector2{l_button2, r_button2};
	settings_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/70, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), sound_volume, buttons_selector2});

}

void MenuGUIView::initCreatePopup(){
	create_popup.setHidden();
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/6.f), "Creer une partie :D"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f), "Mode"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*2.f), "Argent de depart"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*3.f), "Nombre de joueurs max:"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*4.f), "Nombre max de maison:"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*5.f), "Nombre max d'hotel:"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*6.f), "Duree de la partie (min):"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*7.f), "Duree d'un tour (sec)"});

	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*2.f+WINDOW_WIDTH/50), "par defaut: 1500(normal), 3000(rapide)"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*4.f+WINDOW_WIDTH/50), "en mode rapide: pas de limite"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*5.f+WINDOW_WIDTH/50), "en mode rapide: pas de limite"});
	create_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*6.f+WINDOW_WIDTH/50), "par defaut: pas de limite(normal), 50 min(rapide)"});
											//(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f)

	create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f+WINDOW_HEIGHT/4.f), BACK_BUTTON_PATH});
	create_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/25.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f+WINDOW_HEIGHT/4.f), OK_BUTTON_PATH});
	std::vector<std::string> game_mode{"classique", "rapide"};
	std::vector<std::string> start_money{"par defaut","1500", "2000", "2500", "3000", "888"};
	std::vector<std::string> player_nbr{"2", "3", "4", "5", "6"};

	std::vector<std::string> max_house{"par defaut", "2", "3", "4", "10"};
	std::vector<std::string> max_hotel{"par defaut", "2", "3", "4", "10"};

	std::vector<std::string> game_time{"par defaut","5", "10", "15", "20"};
	std::vector<std::string> turn_time{"20", "30", "40", "50", "60"};

	DirectionImButton* l_button1= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button1= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector1{l_button1, r_button1};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f), game_mode, buttons_selector1});


	DirectionImButton* l_button2= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*2.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button2= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*2), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector2{l_button2, r_button2};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*2), start_money, buttons_selector2});


	DirectionImButton* l_button3= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*3.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button3= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*3), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector3{l_button3, r_button3};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*3), player_nbr, buttons_selector3});

	DirectionImButton* l_button4= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*4.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button4= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*4), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector4{l_button4, r_button4};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*4), max_house, buttons_selector4});

	DirectionImButton* l_button5= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*5.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button5= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*5), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector5{l_button5, r_button5};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*5), max_hotel, buttons_selector5});

	DirectionImButton* l_button6= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*6.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button6= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*6), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector6{l_button6, r_button6};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*6), game_time, buttons_selector6});

	DirectionImButton* l_button7= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f+WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10*7.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button7= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f) - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*7), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector7{l_button7, r_button7};
	create_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, (WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f- WINDOW_WIDTH/8.f + WINDOW_WIDTH/50.f ) + WINDOW_WIDTH/50.f, WINDOW_HEIGHT/6+WINDOW_HEIGHT/10.f*7), turn_time, buttons_selector7});

}

void MenuGUIView::initJoinPopup(){
	join_popup.setHidden();
	join_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4.f), "Rejoindre une partie :D"});
	join_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4+100.f), "Entrez le code de jeu"});
<<<<<<< HEAD
	join_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
	join_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_HEIGHT/15.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2+WINDOW_HEIGHT/10, WINDOW_HEIGHT/2.f), SEND_BUTTON_PATH});
=======
	join_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/6.f, WINDOW_HEIGHT/6.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
	join_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/6.f, WINDOW_HEIGHT/6.f, WINDOW_WIDTH/2, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), OK_BUTTON_PATH});
>>>>>>> fc35fb8ac88e6009ccdedc2f7a5b9900ab9ae7ff
	join_popup.addInput(new InputBox{ObjectInfo<>(WINDOW_WIDTH/8, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f-WINDOW_WIDTH/15, WINDOW_HEIGHT/2),RANK_COLOR, SERIF_FONT_PATH});

}

void MenuGUIView::draw() {
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

std::string MenuGUIView::getCreateCmd() {
		// /create [mode] [startMoney] [MaxPlayer] [MaxHome] [maxTimeGame] [maxTimeTurn]
		std::string cmd = "/create";
		std::vector<std::string> game_parameters;
		const std::vector<std::unique_ptr<Selector>>& selectors = create_popup.getAllSelectors();
		for (const auto& selector : selectors) {
			game_parameters.push_back(selector->getActualString());
		}
		// mode
		std::string mode = (game_parameters.at(0) == "classique") ? "normal" : "fast";
		std::string start_money = (game_parameters.at(1) == "par defaut")? "null" : game_parameters.at(1);
		std::string max_player = game_parameters.at(2);
		std::string max_house;
		std::string max_hotel;

		if (mode == "fast") {
			max_house = "null";
			max_hotel = "null";
		}
		else {
			max_house = (game_parameters.at(3) == "par defaut")? "null" : game_parameters.at(3);
			max_hotel = (game_parameters.at(4) == "par defaut")? "null" : game_parameters.at(4);
		}

		std::string game_time = (game_parameters.at(5) == "par defaut")? "null" : std::to_string(stoi(game_parameters.at(5))*60);
		std::string turn_time = game_parameters.at(6);

		cmd += " " + mode;
		cmd += " " + start_money;
		cmd += " " + max_player;
		cmd += " " + max_house;
		cmd += " " + max_hotel;
		cmd += " " + game_time;
		cmd += " " + turn_time;
		
		return cmd;
}
#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"

class CreateGameGUIController; // forward declaration

class CreateGameGUIView: public AbstractGUIView {

	// Objects
	ModalBox popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

	public:

	//using AbstractGUIView::AbstractGUIView;
	explicit CreateGameGUIView(sf::RenderWindow* window) : AbstractGUIView(window){	// w/4 -> là ou commence la fenetre pop up
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/4.f), "Créer une partie :D"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "Nombre de joueur:"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), "Mode:"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), "Chrono:"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*4.f), "Durée enchère:"});

		//creer le button en attribut pour qu'il soit utilisable avec le controller ?
		popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/12.f, WINDOW_HEIGHT/12.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f), BACK_BUTTON_PATH});
		popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/12.f, WINDOW_HEIGHT/12.f, WINDOW_WIDTH/4*3-WINDOW_WIDTH/12.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f), OK_BUTTON_PATH});
	}

	
	~CreateGameGUIView()=default;

	void draw() override {
		popup.draw(*window);
	}

	friend class CreateGameGUIController;

};
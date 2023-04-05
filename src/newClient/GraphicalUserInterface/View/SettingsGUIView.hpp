#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"

class SettingsGUIController; // forward declaration

class SettingsGUIView: public AbstractGUIView {

	// Objects
	ModalBox popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};
	

	public:

	//using AbstractGUIView::AbstractGUIView;
	explicit SettingsGUIView(sf::RenderWindow* window) : AbstractGUIView(window){	// w/4 -> là ou commence la fenetre pop up
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f, WINDOW_HEIGHT/4.f), "Réglages :D"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10.f), "Taille de fenêtre:"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*2.f), "Son:"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*3.f), "Changer pseudo:"});
		popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*4.f), "Supprimer son compte:"});
	}											//w/50 c'est la taille de police
	
	~SettingsGUIView()=default;

	void draw() override {
		
		popup.draw(*window);
	}

	friend class SettingsGUIController;

};
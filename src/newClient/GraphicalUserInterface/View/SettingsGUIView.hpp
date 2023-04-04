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
	explicit ConnectionGUIView(sf::RenderWindow* window) : AbstractGUIView(window){
		popup.addImage(new Image logo{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_WIDTH/2.f * 145.f/788.f, WINDOW_WIDTH/4.f , WINDOW_HEIGHT/10.f), LOGO_PATH});
		
	}
	
	~SettingsGUIView()=default;

	void draw() override {
		
		popup.draw(*window);
	}

	friend class SettingsGUIController;

};
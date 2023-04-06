/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


class FriendsGUIController; // forward declaration

class FriendsGUIView: public AbstractGUIView {

	// Objects
	ImageButton back_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, 0+15,0+15), BACK_BUTTON_PATH};

	Box messaging_box{ObjectInfo<>(WINDOW_WIDTH/2.f+WINDOW_WIDTH/6.f, WINDOW_WIDTH/4*2 , WINDOW_WIDTH/25.f , WINDOW_HEIGHT/10.f), WHITE};
	Text other_user{ObjectInfo<>(0.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/25+50 , WINDOW_HEIGHT/10.f), "Nom de l'ami"};
	Box conversation_bbox{ObjectInfo<>(WINDOW_WIDTH/2-WINDOW_WIDTH/10.f, WINDOW_WIDTH/4*2-WINDOW_WIDTH , WINDOW_WIDTH/20.f , WINDOW_HEIGHT/8.f), RANK_COLOR};

public:

	using AbstractGUIView::AbstractGUIView;
	
	~FriendsGUIView()=default;

	void draw() override {
		back_button.draw(*window);
		messaging_box.draw(*window);
		other_user.draw(*window);
		conversation_bbox.draw(*window);
	}

	void clear();

	friend class FriendsGUIController;

};
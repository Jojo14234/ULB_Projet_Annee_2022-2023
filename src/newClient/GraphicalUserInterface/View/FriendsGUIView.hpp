/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


class FriendsGUIController; // forward declaration

class FriendsGUIView: public AbstractGUIView {

	// Objects

	ImageButton back_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, 0+15,0+15), BACK_BUTTON_PATH};

	//MESSAGE 
	Box messaging_box{ObjectInfo<>(WINDOW_WIDTH/2.f+WINDOW_WIDTH/6.f, WINDOW_WIDTH/4*2 , WINDOW_WIDTH/25.f , WINDOW_HEIGHT/10.f), WHITE};
	Text other_user{ObjectInfo<>(0.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/25+50 , WINDOW_HEIGHT/10.f), "Nom de l'ami"};
	Box conversation_bbox{ObjectInfo<>(WINDOW_WIDTH/2+WINDOW_WIDTH/8.f, WINDOW_WIDTH/4*2-WINDOW_WIDTH/10 , WINDOW_WIDTH/18.f , WINDOW_HEIGHT/6.f), TOP_BOX_COLOR};
	Text messages{ObjectInfo<>(0.f, WINDOW_WIDTH/60.f, WINDOW_WIDTH/25+50 , WINDOW_HEIGHT/6+WINDOW_WIDTH/65.f), "Miaou Miaou"};

	InputBox message_input{ObjectInfo<>(WINDOW_WIDTH/2+WINDOW_WIDTH/8.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/18.f, WINDOW_HEIGHT/6.f + WINDOW_WIDTH/4*2-WINDOW_WIDTH/10), BOX_COLOR, SERIF_FONT_PATH};
	Border message_border{message_input, 5};

	//FRIEND REQUEST 
	Box request_box{ObjectInfo<>(WINDOW_WIDTH/2.f-WINDOW_WIDTH/6.f - WINDOW_WIDTH/25.f ,WINDOW_HEIGHT/5  ,WINDOW_WIDTH/2.f+WINDOW_WIDTH/6.f + WINDOW_WIDTH/18 ,WINDOW_HEIGHT/10.f ), RANK_COLOR};
	Text friend_request{ObjectInfo<>(0.f, WINDOW_WIDTH/60.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.f + 100 , WINDOW_HEIGHT/8.f), "MAchin vous a friend request"};
	//ImageButton yes_button
	//ImageButton no_button

	//FRIEND LIST
	Box friend_list_box{ObjectInfo<>( WINDOW_WIDTH/2.f-WINDOW_WIDTH/6.f - WINDOW_WIDTH/25.f, WINDOW_HEIGHT/2+WINDOW_HEIGHT/6,WINDOW_WIDTH/2.f+WINDOW_WIDTH/6.f + WINDOW_WIDTH/18, WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5), RANK_COLOR};

	Text friend_list{ObjectInfo<>(0.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.f + 100 , WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5+10), "Liste d'amis"};

	//Box friend_list2_bbox{ObjectInfo<>( , , , ), TOP_BOX_COLOR};
	//5 friends box + bouton message et bouton supprimer pour chacun 


public:

	using AbstractGUIView::AbstractGUIView;
	
	~FriendsGUIView()=default;

	void draw() override {
		//MESSAGE
		back_button.draw(*window);
		messaging_box.draw(*window);
		other_user.draw(*window);
		conversation_bbox.draw(*window);
		messages.draw(*window);
		message_border.draw(*window);
		message_input.draw(*window);

		//FRIEND REQUEST
		request_box.draw(*window);
		friend_request.draw(*window);

		//FRIEND LIST
		friend_list_box.draw(*window);
		friend_list.draw(*window);
	}

	void clear();

	friend class FriendsGUIController;

};
/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"



class FriendsGUIController; // forward declaration

class FriendsGUIView: public AbstractGUIView {

	// Objects

	ImageButton back_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, 0+15,0+15), BACK_BUTTON_PATH};

	//MESSAGE-------------------------------------------------------------- 
	Box messaging_box{ObjectInfo<>(WINDOW_WIDTH/2.f+WINDOW_WIDTH/6.f, WINDOW_WIDTH/4*2 , WINDOW_WIDTH/25.f , WINDOW_HEIGHT/10.f), WHITE};
	Text other_user{ObjectInfo<>(0.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/25+50 , WINDOW_HEIGHT/10.f), "Nom de l'ami"};
	Box conversation_bbox{ObjectInfo<>(WINDOW_WIDTH/2+WINDOW_WIDTH/8.f, WINDOW_WIDTH/4*2-WINDOW_WIDTH/10 , WINDOW_WIDTH/18.f , WINDOW_HEIGHT/6.f), TOP_BOX_COLOR};
	Text messages{ObjectInfo<>(0.f, WINDOW_WIDTH/60.f, WINDOW_WIDTH/25+50 , WINDOW_HEIGHT/6+WINDOW_WIDTH/65.f), "Miaou Miaou"};

	InputBox message_input{ObjectInfo<>(WINDOW_WIDTH/2+WINDOW_WIDTH/8.f- WINDOW_HEIGHT/15.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/18.f, WINDOW_HEIGHT/6.f + WINDOW_WIDTH/4*2-WINDOW_WIDTH/10), BOX_COLOR, SERIF_FONT_PATH};
	Border message_border{message_input, 5};
	ImageButton send_button{ObjectInfo<>(WINDOW_HEIGHT/15.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2+WINDOW_WIDTH/8.f + WINDOW_HEIGHT/15*1/2, WINDOW_HEIGHT/6.f + WINDOW_WIDTH/4*2-WINDOW_WIDTH/10), SEND_BUTTON_PATH};

	//FRIEND REQUEST-------------------------------------------------------------- 
	Box manager_box{ObjectInfo<>(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f ,WINDOW_HEIGHT/5  ,WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18 ,WINDOW_HEIGHT/10.f ), WHITE};
	Text friend_request{ObjectInfo<>(0.f, WINDOW_WIDTH/60.f, WINDOW_WIDTH*8/12.f + 100 , WINDOW_HEIGHT/8.f), "Demandes d'ami.e"};
	ImageButton request_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, (WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18) +((WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f)/2)-WINDOW_WIDTH/16.f-50, WINDOW_HEIGHT/5.f), YES_BUTTON_PATH};
	ImageButton ask_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, (WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18)+(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f)/2,WINDOW_HEIGHT/5.f), NO_BUTTON_PATH};
	ModalBox request_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};
	ModalBox ask_popup{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};

	//FRIEND LIST--------------------------------------------------------------
	//Box friend_list_box{ObjectInfo<>(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f, WINDOW_HEIGHT*8/12,WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18, WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5), WHITE};

	Text friend_list{ObjectInfo<>(0.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH*8/12.f + 100 , WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5+10), "Liste d'amis"};

	ScrollBox<FriendBox> scroll{ObjectInfo<>(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f, WINDOW_HEIGHT*8/12,WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18, WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5), WINDOW_WIDTH/20.f, WHITE};


public:

	explicit FriendsGUIView(sf::RenderWindow* window);
		// TODO prendre les size des attributs et mettre ici
	
	~FriendsGUIView()=default;

	void draw() override;

	void clear();

	friend class FriendsGUIController;

	void initFriendBox();
	void initRequestPopup();
	void initAskPopup();

};
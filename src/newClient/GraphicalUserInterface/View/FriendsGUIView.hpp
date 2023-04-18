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
	Box request_box{ObjectInfo<>(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f ,WINDOW_HEIGHT/5  ,WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18 ,WINDOW_HEIGHT/10.f ), WHITE};
	Text friend_request{ObjectInfo<>(0.f, WINDOW_WIDTH/60.f, WINDOW_WIDTH*8/12.f + 100 , WINDOW_HEIGHT/8.f), "MAchin vous a friend request"};
	ImageButton yes_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, (WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18) +((WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f)/2)-WINDOW_WIDTH/16.f-50, WINDOW_HEIGHT/5.f), YES_BUTTON_PATH};
	ImageButton no_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, (WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18)+(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f)/2,WINDOW_HEIGHT/5.f), NO_BUTTON_PATH};

	//FRIEND LIST--------------------------------------------------------------
	//Box friend_list_box{ObjectInfo<>(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f, WINDOW_HEIGHT*8/12,WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18, WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5), WHITE};

	Text friend_list{ObjectInfo<>(0.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH*8/12.f + 100 , WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5+10), "Liste d'amis"};

	ScrollBox<FriendBox> scroll{ObjectInfo<>(WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f, WINDOW_HEIGHT*8/12,WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18, WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5), WINDOW_WIDTH/20.f, WHITE};


public:

	explicit FriendsGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {
		// TODO prendre les size des attributs et mettre ici
		const double size_x = WINDOW_WIDTH*4/12.f - WINDOW_WIDTH/25.f;
		const double size_y = WINDOW_WIDTH/20.f;
		const double pos_x = WINDOW_WIDTH*8/12.f + WINDOW_WIDTH/18;
		const double pos_y = WINDOW_WIDTH/30.f + WINDOW_HEIGHT/8.f+WINDOW_HEIGHT/5+30;
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y), "xX_.h4w3n._Xx"});
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y+10+size_y), "lolcatz1287"});
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y+(10+size_y)*2), "m4cr0n_c4lvitie"});
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y+(10+size_y)*3), "__t0rtUe._.m4UdiT3__"});
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y+(10+size_y)*4), "x3l0w0"});
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y+(10+size_y)*5), "HUGOGO"});
		this->scroll.addObject(new FriendBox{ObjectInfo<>(size_x, size_y, pos_x, pos_y+(10+size_y)*5), "youhou"});
		this->scroll.setMaxObjToShow(6);
	}
	
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
		send_button.draw(*window);

		//FRIEND REQUEST
		request_box.draw(*window);
		friend_request.draw(*window);
		yes_button.draw(*window);
		no_button.draw(*window);

		this->scroll.draw(*window);
		friend_list.draw(*window);
		
	}

	void clear();

	friend class FriendsGUIController;

};
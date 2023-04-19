#include "FriendsGUIView.hpp"

FriendsGUIView::FriendsGUIView(sf::RenderWindow* window) : AbstractGUIView(window){
	this->initFriendBox();
	this->initRequestPopup();
	this->initAskPopup();
}

void FriendsGUIView::initFriendBox(){
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

void FriendsGUIView::initRequestPopup(){
	request_popup.setHidden();
	request_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
	request_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4.f), "Demandes d'ami :D"});
	request_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4+100.f), "Accepte ou refuse la demande de:"});
	std::vector<std::string> maybe_new_friends{"bip", "boup", "bop"};
	DirectionImButton* l_button= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f,(WINDOW_WIDTH/2.f-WINDOW_WIDTH/15) + WINDOW_WIDTH/8.f , WINDOW_HEIGHT/2.f), RIGHT_BUTTON_PATH};
	DirectionImButton* r_button= new DirectionImButton{ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_WIDTH/50.f, WINDOW_WIDTH/2.f-WINDOW_WIDTH/15-WINDOW_WIDTH/50.f, WINDOW_HEIGHT/2.f), LEFT_BUTTON_PATH};
	std::vector<DirectionImButton*> buttons_selector{l_button, r_button};
	request_popup.addSelector(new Selector{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/2.f-WINDOW_WIDTH/15, WINDOW_HEIGHT/2), maybe_new_friends, buttons_selector});
	request_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/2-WINDOW_WIDTH/26, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/8.f), YES_BUTTON_PATH});
	request_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/2+WINDOW_WIDTH/26, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/8.f), NO_BUTTON_PATH});

}

void FriendsGUIView::initAskPopup(){
	ask_popup.setHidden();
	ask_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_WIDTH/25.f, WINDOW_HEIGHT/25.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4+WINDOW_HEIGHT/10*5.f-WINDOW_HEIGHT/12.f+WINDOW_HEIGHT/25.f), BACK_BUTTON_PATH});
	ask_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4.f), "Ajoutez un.e ami.e :D"});
	ask_popup.addText(new Text{ObjectInfo<>(0, WINDOW_WIDTH/50, WINDOW_WIDTH/2.f-WINDOW_WIDTH/8, WINDOW_HEIGHT/4+100.f), "Entrez son pseudo:"});
	ask_popup.addButton(new ImageButton{ObjectInfo<>(WINDOW_HEIGHT/15.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f-WINDOW_WIDTH/15.f+WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2), SEND_BUTTON_PATH});
	ask_popup.addInput(new InputBox{ObjectInfo<>(WINDOW_WIDTH/6, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f-WINDOW_WIDTH/15, WINDOW_HEIGHT/2),RANK_COLOR, SERIF_FONT_PATH});

}

void FriendsGUIView::draw() {
		//MESSAGE
		back_button.draw(*window);
		messaging_box.draw(*window);
		other_user.draw(*window);
		conversation_bbox.draw(*window);
		messages.draw(*window);
		message_border.draw(*window);
		message_input.draw(*window);
		send_button.draw(*window);

		this->scroll.draw(*window);
		friend_list.draw(*window);

		//FRIEND REQUEST
		manager_box.draw(*window);
		friend_request.draw(*window);
		request_button.draw(*window);
		ask_button.draw(*window);
		request_popup.draw(*window);
		ask_popup.draw(*window);		
	}
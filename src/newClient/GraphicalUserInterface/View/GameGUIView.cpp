#include "GameGUIView.hpp"

void GameGUIView::setStartGame(bool visible){
	if (visible == false){
		button_mode = "";
		startgame_button.setHidden();}
	else {
		hideAllButton();
		button_mode = "start_game";
		startgame_button.setVisible();}}

void GameGUIView::setStartRound(bool visible){
	if (visible == false){
		button_mode = "";
		mortgage_button.setHidden();
		unmortgage_button.setHidden();
		sell_button.setHidden();
		construct_button.setHidden();
		exchange_button.setHidden();
		roll_dice_button.setHidden();}
	else {
		hideAllButton();
		button_mode = "start_round";
		mortgage_button.setVisible();
		unmortgage_button.setVisible();
		sell_button.setVisible();
		construct_button.setVisible();
		exchange_button.setVisible();
		roll_dice_button.setVisible();}}


void GameGUIView::setCellRound(bool visible){
	if (visible == false){
		button_mode = "";
		buy_button.setHidden();
		no_buy_button.setHidden();}
	else {
		hideAllButton();
		button_mode = "empty_cell";
		buy_button.setVisible();
		no_buy_button.setVisible();}}

void GameGUIView::setCardSpeRound(bool visible){
	if (visible == false){
		button_mode = "";
		paid_button.setHidden();
		draw_card_button.setHidden();}	
	else{
		hideAllButton();
		button_mode = "specard_cell";
		paid_button.setVisible();
		draw_card_button.setVisible();}}

void GameGUIView::setPrisonRound(bool visible){
	if (visible == false){
		button_mode = "";
		paid_prison_button.setHidden();
		roll_dice_prison_button.setHidden();
		card_prison_button.setHidden();}
	else{
		hideAllButton();
		button_mode = "on_prison";
		paid_prison_button.setVisible();
		roll_dice_prison_button.setVisible();
		card_prison_button.setVisible();
	}}

void GameGUIView::setExchangeRound(bool visible){
	if (visible == false){
		button_mode = "";
		yes_exchange_button.setHidden(); 
		no_exchange_button.setHidden();}
	else{
		hideAllButton();
		button_mode = "exchange_round";
		yes_exchange_button.setVisible(); 
		no_exchange_button.setVisible();
	}
}

void GameGUIView::setBankruptRound(bool visible){
	if (visible == false){
		button_mode = "";
		sell_bankrupt_button.setHidden();
		give_up_button.setHidden();
	}
	else{
		hideAllButton(); 
		button_mode = "bankrupt_round";
		sell_bankrupt_button.setVisible(); 
		give_up_button.setVisible(); 
	}
}

void GameGUIView::setAuctionRound(bool visible){
	if (visible == false){
		button_mode = "";
		button_zone.setVisible();
		auction_box.setHidden();}
	else{
		hideAllButton(); 
		button_zone.setHidden();
		button_mode = "auction_round";
		auction_box.setVisible();}
}

void GameGUIView::setSpeRound(bool visible){
	if(visible == false){
		setBoardClickMode(visible);
		leave_button.setHidden();}
	else{
		hideAllButton(); 
		setBoardClickMode(visible);
		leave_button.setVisible();
	}
}

void GameGUIView::setJoinAuctionRound(bool visible){
	if(visible == false){
		button_mode = "";
		participate_button.setHidden();}
	else{
		hideAllButton(); 
		button_mode = "participate_round";
		participate_button.setVisible();}
}

void GameGUIView::hideAllButton(){

	//false = hide , true = visible

	setStartGame(false);
	setStartRound(false);
	setCellRound(false);
	setCardSpeRound(false);
	setPrisonRound(false);
	setExchangeRound(false);
	setBankruptRound(false);
	setSpeRound(false);
	setJoinAuctionRound(false);

	auction_box.setHidden();
	exchange_box.setHidden();
}

GameGUIView::GameGUIView(sf::RenderWindow* window) : AbstractGUIView(window),board{}{
	card_title.setBold();


	hideAllButton();

	gamecode_box.setHidden();
	logo.setHidden();
	card_text.setHidden();
}

void GameGUIView::draw() {
	board.draw(*window);

	button_zone.draw(*window);

	drawStartGame();

	drawStartRound();

	drawCellRound();

	drawCardSpeRound();

	drawPrisonRound();

	drawExchangeRound();

	drawBankruptRound();

	

	drawJoinAuction();

	gamecode_box.draw(*window);
	dice.draw(*window);
	info_box.draw(*window);
	message_box.draw(*window);
	exchange_box.draw(*window);
	
	logo.draw(*window);
	card_zone.draw(*window);
	card_text.draw(*window);
	card_title.draw(*window);
	auction_box.draw(*window);
	drawSpeRound();
}

void GameGUIView::drawStartGame(){
	startgame_button.draw(*window);}

void GameGUIView::drawStartRound(){
	mortgage_button.draw(*window);
	unmortgage_button.draw(*window);
	sell_button.draw(*window);
	construct_button.draw(*window);
	exchange_button.draw(*window);
	roll_dice_button.draw(*window);}

void GameGUIView::drawCellRound(){
	buy_button.draw(*window);
	no_buy_button.draw(*window);}

void GameGUIView::drawCardSpeRound(){
	paid_button.draw(*window);
	draw_card_button.draw(*window);}

void GameGUIView::drawPrisonRound(){
	paid_prison_button.draw(*window);
	roll_dice_prison_button.draw(*window);
	card_prison_button.draw(*window);}

void GameGUIView::drawExchangeRound(){
	yes_exchange_button.draw(*window);
	no_exchange_button.draw(*window);
}

void GameGUIView::drawBankruptRound(){
	sell_bankrupt_button.draw(*window);
	give_up_button.draw(*window);
}

void GameGUIView::drawSpeRound(){leave_button.draw(*window);}

void GameGUIView::drawJoinAuction(){participate_button.draw(*window);}

//method for setting the game
void GameGUIView::startTurn(){
	this->dice.setVisible();
    this->message_box.setString("C'est votre tour!");
	this->setStartRound(true);
}

void GameGUIView::endTurn(){
    this->dice.setHidden();
	this->setStartRound(false);
}

void GameGUIView::setBoardClickMode(bool clickable){board_click = clickable;}
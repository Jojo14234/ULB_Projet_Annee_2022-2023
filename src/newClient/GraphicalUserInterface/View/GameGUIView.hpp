/**
 * Project Untitled
 */

#pragma once

#include "AbstractGUIView.hpp"


#include "GameObject/Board.hpp"
#include "GameObject/InfoBox.hpp"
#include "Objects/ImageButton.hpp"
#include "GameObject/AuctionBox.hpp"
#include "GameObject/MessageBox.hpp"

class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {
	Board board;
	InfoBox info_box{ObjectInfo<>(400, 400,window->getSize().x -400,window->getSize().y - 350)};

	Box button_zone{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };

	ImageButton mortgage_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/6*0  ), MORTGAGE_BUTTON};
	ImageButton unmortgage_button{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 *1 ), UNMORTGAGE_BUTTON};
	ImageButton sell_button{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 *2), SELL_BUTTON};
	ImageButton construct_button{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 * 3), CONSTRUCT_BUTTON};
	ImageButton exchange_button{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 *4), EXCHANGE_BUTTON};
	ImageButton roll_dice_button{ObjectInfo<>(200, 150 ,50, window->getSize().y/6  * 5), ROLLDICE_BUTTON};

	ImageButton buy_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/2*0  ), BUY_BUTTON};
	ImageButton no_buy_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/2*1  ), NOBUY_BUTTON};

	ImageButton draw_card_button{ObjectInfo<>(200, 150 ,50,0  ), DRAWCARD_BUTTON};

	ImageButton paid_button{ObjectInfo<>(200, 150 ,50,0 ), PAID_BUTTON};

	ImageButton paid_prison_button{ObjectInfo<>(200, 150 ,50,0 ), PAID_BUTTON};
	ImageButton roll_dice_prison_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*1 ), ROLLDICE_BUTTON};
	ImageButton card_prison_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*2 ), PRISONCARD_BUTTON};

	ImageButton yes_exchange_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*0 ), YES_BUTTON};
	ImageButton no_exchange_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*1 ), NO_BUTTON};

	ImageButton sell_bankrupt_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*0 ), SELL_BUTTON};
	ImageButton give_up_button{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*1 ), FORFAIT_BUTTON};
	
	std::vector<std::string> colorlist{"red","blue","green","cyan","magenta","yellow"};   //pour tester à enlever

	AuctionBox auction_box{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };  //boutons enchères

	std::string button_mode = "";
 
	MessageBox message_box{ObjectInfo<>(800,60,350,5)};  //zone en haut qui affiche les actions des joueurs
	// Objects

	void setStartRound(bool visible){
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


	void setEmptyCellRound(bool visible){
		if (visible == false){
			button_mode = "";
			buy_button.setHidden();
			no_buy_button.setHidden();}
		else {
			hideAllButton();
			button_mode = "empty_cell";
			buy_button.setVisible();
			no_buy_button.setVisible();}}

	void setOppCellRound(bool visible){
		if (visible == false){
			button_mode = "";
			paid_button.setHidden();}	
		else{
			hideAllButton();
			button_mode = "paid_cell";
			paid_button.setVisible();}}
	
	void setCardCellRound(bool visible){
		if (visible == false){
			button_mode = "";
			draw_card_button.setHidden();}
		else{
			hideAllButton();
			button_mode = "card_cell";
			draw_card_button.setVisible();}}
		

	void setPrisonRound(bool visible){
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

	void setExchangeRound(bool visible){
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
	
	void setBankruptRound(bool visible){
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

	void setAuctionRound(bool visible){
		if (visible == false){
			button_mode = "";
			button_zone.setVisible();
			auction_box.setHidden();}
		else{
			hideAllButton(); 
			button_zone.setHidden();
			button_mode = "auction_round";
			auction_box.setVisible();
		}
	}

	void hideAllButton(){

		//true = hide , false = visible
	
		setStartRound(false);
		setEmptyCellRound(false);
		setOppCellRound(false);
		setCardCellRound(false);
		setPrisonRound(false);
		setExchangeRound(false);
		setBankruptRound(false);

		auction_box.setHidden();
	}

public:

	explicit GameGUIView(sf::RenderWindow* window) : AbstractGUIView(window)
	,board{}{

		message_box.setString("C'est le tour de miaou");

		hideAllButton();

		setAuctionRound(true);
	

	}

	
	~GameGUIView()=default;



	void draw() override {
		board.draw(*window);

		button_zone.draw(*window);

		drawStartRound();

		drawEmptyCellRound();
		drawOppCellRound();
		drawCardCellRound();

		drawPrisonRound();

		drawExchangeRound();

		drawBankruptRound();

		info_box.draw(*window);
		message_box.draw(*window);
		auction_box.draw(*window);
	}

	void drawStartRound(){
		mortgage_button.draw(*window);
		unmortgage_button.draw(*window);
		sell_button.draw(*window);
		construct_button.draw(*window);
		exchange_button.draw(*window);
		roll_dice_button.draw(*window);}

	void drawEmptyCellRound(){
		buy_button.draw(*window);
		no_buy_button.draw(*window);}

	void drawOppCellRound(){
		paid_button.draw(*window);}

	void drawCardCellRound(){
		draw_card_button.draw(*window);}
	
	void drawPrisonRound(){
		paid_prison_button.draw(*window);
		roll_dice_prison_button.draw(*window);
		card_prison_button.draw(*window);}

	void drawExchangeRound(){
		yes_exchange_button.draw(*window);
		no_exchange_button.draw(*window);
	}

	void drawBankruptRound(){
		sell_bankrupt_button.draw(*window);
		give_up_button.draw(*window);
	}
	void clear();

	//method for setting the game

	void startTurn(){
        //this->showDice(); à rajouter
        this->message_box.setString("C'est votre tour!");
		this->setStartRound(true);
    }

	void endTurn(){
        //this->hideDice(); à rajouter
		this->setStartRound(false);
    }


	friend class GameGUIController;
	//Board* getBoard() { return &board; }

};
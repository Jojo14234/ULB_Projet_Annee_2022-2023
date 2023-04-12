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
	InfoBox info_box;
	AuctionBox auction_box;

	Box start_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };
	ImageButton mortgage{ObjectInfo<>(200, 150 ,50,window->getSize().y/6*0  ), MORTGAGE_BUTTON};
	ImageButton unmortgage{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 *1 ), UNMORTGAGE_BUTTON};
	ImageButton  sell{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 *2), SELL_BUTTON};
	ImageButton construct{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 * 3), CONSTRUCT_BUTTON};
	ImageButton exchange{ObjectInfo<>(200, 150 ,50, window->getSize().y/6 *4), EXCHANGE_BUTTON};
	ImageButton roll_dice{ObjectInfo<>(200, 150 ,50, window->getSize().y/6  * 5), ROLLDICE_BUTTON};

	Box emptycell_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };
	ImageButton buy{ObjectInfo<>(200, 150 ,50,window->getSize().y/2*0  ), BUY_BUTTON};
	ImageButton no_buy{ObjectInfo<>(200, 150 ,50,window->getSize().y/2*1  ), NOBUY_BUTTON};

	Box cardcell_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };
	ImageButton draw_card{ObjectInfo<>(200, 150 ,50,0  ), DRAWCARD_BUTTON};

	Box oppcell_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };
	ImageButton paid{ObjectInfo<>(200, 150 ,50,0 ), PAID_BUTTON};

	Box prison_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };
	ImageButton paid_prison{ObjectInfo<>(200, 150 ,50,0 ), PAID_BUTTON};
	ImageButton roll_dice_prison{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*1 ), ROLLDICE_BUTTON};
	ImageButton card_prison{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*2 ), PRISONCARD_BUTTON};

	Box exchange_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red};
	ImageButton yes_exchange{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*0 ), YES_BUTTON};
	ImageButton no_exchange{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*1 ), NO_BUTTON};

	Box bankrupt_round{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red};
	ImageButton sell_bankrupt{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*0 ), SELL_BUTTON};
	ImageButton give_up{ObjectInfo<>(200, 150 ,50,window->getSize().y/3*1 ), FORFAIT_BUTTON};
	
	std::vector<std::string> colorlist{"red","blue","green","cyan","magenta","yellow"};   //pour tester à enlever
	
	MessageBox message_box;
	// Objects

	void hideStartRound(bool hidden){
		if (hidden == true){
			start_round.setHidden();
			mortgage.setHidden();
			unmortgage.setHidden();
			sell.setHidden();
			construct.setHidden();
			exchange.setHidden();
			roll_dice.setHidden();}
		else {
			start_round.setVisible();
			mortgage.setVisible();
			unmortgage.setVisible();
			sell.setVisible();
			construct.setVisible();
			exchange.setVisible();
			roll_dice.setVisible();}}


	void hideEmptyCellRound(bool hidden){
		if (hidden == true){
			emptycell_round.setHidden();
			buy.setHidden();
			no_buy.setHidden();}
		else {
			emptycell_round.setVisible();
			buy.setVisible();
			no_buy.setVisible();}}

	void hideOppCellRound(bool hidden){
		if (hidden == true){
			oppcell_round.setHidden();
			paid.setHidden();}	
		else{
			oppcell_round.setVisible();
			paid.setVisible();}}
	
	void hideCardCellRound(bool hidden){
		if (hidden == true){
			cardcell_round.setHidden();
			draw_card.setHidden();}
		else{
			cardcell_round.setVisible();
			draw_card.setVisible();}}
		

	void hidePrisonRound(bool hidden){
		if (hidden == true){
			prison_round.setHidden();
			paid_prison.setHidden();
			roll_dice_prison.setHidden();
			card_prison.setHidden();}
		else{
			prison_round.setVisible();
			paid_prison.setVisible();
			roll_dice_prison.setVisible();
			card_prison.setVisible();
		}}

	void hideExchangeRound(bool hidden){
		if (hidden == true){
			exchange_round.setHidden(); 
			yes_exchange.setHidden(); 
			no_exchange.setHidden();}
		else{
			exchange_round.setVisible(); 
			yes_exchange.setVisible(); 
			no_exchange.setVisible();
		}
	}

	/*
	void hideAunctionRound(bool hidden){
		if (hidden == true){}
		else{}
	}*/

	void hideBankruptRound(bool hidden){
		if (hidden == true){
			bankrupt_round.setHidden(); 
			sell_bankrupt.setHidden();
			give_up.setHidden();
		}
		else{
			bankrupt_round.setVisible();  
			sell_bankrupt.setVisible(); 
			give_up.setVisible(); 
		}
	}

public:

	explicit GameGUIView(sf::RenderWindow* window) : AbstractGUIView(window)
	,board{}
	,info_box{ObjectInfo<>(400, 400,window->getSize().x -400,window->getSize().y - 350)}
	,message_box{ObjectInfo<>(800,60,350,5)}
	,auction_box{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red }
	{
		info_box.initMoney(colorlist,300000);
		info_box.setMoney(4,520);
		message_box.setString("C'est le tour de miaou");


		//true = hide , false = visible
		hideStartRound(true);
		hideEmptyCellRound(true);
		hideOppCellRound(true);
		hideCardCellRound(true);
		hidePrisonRound(true);
		hideExchangeRound(true);
		hideBankruptRound(true);

		auction_box.setHidden();

	}

	
	~GameGUIView()=default;



	void draw() override {
		board.draw(*window);

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
		auction_box.setTextNumber(18880);
	}

	void drawStartRound(){
		start_round.draw(*window);
		mortgage.draw(*window);
		unmortgage.draw(*window);
		sell.draw(*window);
		construct.draw(*window);
		exchange.draw(*window);
		roll_dice.draw(*window);}

	void drawEmptyCellRound(){
		emptycell_round.draw(*window);
		buy.draw(*window);
		no_buy.draw(*window);}

	void drawOppCellRound(){
		oppcell_round.draw(*window);
		paid.draw(*window);}

	void drawCardCellRound(){
		cardcell_round.draw(*window);
		draw_card.draw(*window);}
	
	void drawPrisonRound(){
		prison_round.draw(*window);
		paid_prison.draw(*window);
		roll_dice_prison.draw(*window);
		card_prison.draw(*window);}

	void drawExchangeRound(){
		exchange_round.draw(*window);
		yes_exchange.draw(*window);
		no_exchange.draw(*window);
	}

	void drawAuctionRound(){
		//à rajouter ds une classe à part
	}


	void drawBankruptRound(){
		bankrupt_round.draw(*window);
		sell_bankrupt.draw(*window);
		give_up.draw(*window);
	}
	void clear();

	friend class GameGUIController;
	//Board* getBoard() { return &board; }

};
#pragma once

#include "AbstractGUIView.hpp"


#include "GameObject/Board.hpp"
#include "GameObject/InfoBox.hpp"
#include "Objects/ImageButton.hpp"
#include "GameObject/AuctionBox.hpp"
#include "GameObject/MessageBox.hpp"
#include "GameObject/Dice.hpp"
#include "GameObject/GamecodeBox.hpp"
#include "GameObject/ExchangeBox.hpp"

class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {
	Board board;
	InfoBox info_box{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_HEIGHT/2.25f ,WINDOW_WIDTH/1.33f ,WINDOW_HEIGHT/1.8f)};

	Box button_zone{ObjectInfo<>(WINDOW_WIDTH/5.33f ,WINDOW_HEIGHT ,0 ,0), sf::Color::Red };

	ImageButton startgame_button{ObjectInfo<>(WINDOW_WIDTH/8.f,WINDOW_HEIGHT/9.f ,50,0), START_BUTTON};

	ImageButton mortgage_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0), MORTGAGE_BUTTON};
	ImageButton unmortgage_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f , WINDOW_HEIGHT/6.f), UNMORTGAGE_BUTTON};
	ImageButton sell_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f , WINDOW_HEIGHT/3.f), SELL_BUTTON};
	ImageButton construct_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f , WINDOW_HEIGHT/2.f), CONSTRUCT_BUTTON};
	ImageButton exchange_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f , WINDOW_HEIGHT/1.5f), EXCHANGE_BUTTON};
	ImageButton roll_dice_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f , WINDOW_HEIGHT/1.2f), ROLLDICE_BUTTON};

	ImageButton buy_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0), BUY_BUTTON};
	ImageButton no_buy_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/2.f), NOBUY_BUTTON};

	ImageButton draw_card_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0), DRAWCARD_BUTTON};
	ImageButton paid_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/2.f), PAID_BUTTON};

	ImageButton paid_prison_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0), PAID_BUTTON};
	ImageButton roll_dice_prison_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/3.f), ROLLDICE_BUTTON};
	ImageButton card_prison_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/1.5f), PRISONCARD_BUTTON};

	ImageButton yes_exchange_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0), YES_BUTTON};
	ImageButton no_exchange_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/3.f), NO_BUTTON};

	ImageButton sell_bankrupt_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0), SELL_BUTTON};
	ImageButton give_up_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/3.f), FORFAIT_BUTTON};

	ImageButton leave_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/32.f ,0) ,LEAVE_BUTTON};

	ImageButton participate_button{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f  ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT) ,PARTICIPATE_BUTTON};

	ImageButton leave_button_end{ObjectInfo<>(WINDOW_WIDTH/8.f ,WINDOW_HEIGHT/9.f  ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/3.f) ,LEAVE_BUTTON};

	
	std::vector<std::string> colorlist{"red","blue","green","cyan","magenta","yellow"};   //pour tester à enlever

	AuctionBox auction_box{ObjectInfo<>(WINDOW_WIDTH/5.33f ,WINDOW_HEIGHT ,0,0), sf::Color::Red };  //boutons enchères

	ExchangeBox exchange_box{ObjectInfo<>(WINDOW_WIDTH/5.33f ,WINDOW_HEIGHT ,0,0), sf::Color::Red };

	bool exchange_mode = false;
	bool other_mode = false;

	std::string button_mode = "";
 
	MessageBox message_box{ObjectInfo<>(WINDOW_WIDTH/2.f ,WINDOW_HEIGHT/15.f ,WINDOW_WIDTH/4.57f ,WINDOW_HEIGHT/180.f)};  //zone en haut qui affiche les actions des joueurs

	GamecodeBox gamecode_box{ObjectInfo<>(WINDOW_WIDTH/4.f ,WINDOW_HEIGHT/4.5f ,WINDOW_WIDTH/2.91f ,WINDOW_HEIGHT/4.5f)};

	Dice dice;

	Image logo {ObjectInfo<>(WINDOW_WIDTH/2.6f ,WINDOW_HEIGHT/4.5f ,WINDOW_WIDTH/3.55f ,WINDOW_HEIGHT/4.5f),LOGO_PATH};
	Image card_zone{ObjectInfo<>(WINDOW_WIDTH/4.1f ,WINDOW_HEIGHT/3.f ,WINDOW_WIDTH/2.857f ,WINDOW_HEIGHT/1.8f),CARD_TEXT};
	Text card_text{ObjectInfo<>(0,WINDOW_HEIGHT/45.f ,WINDOW_WIDTH/2.71f ,WINDOW_HEIGHT/1.5f),""};
	Text card_title{ObjectInfo<>(0,WINDOW_HEIGHT/26.47f ,WINDOW_WIDTH/2.735f ,WINDOW_HEIGHT/1.5f),"    CHANCE et\nCAISSE DE COMMU"};

	bool board_click = false;
	// Objects

	void setStartGame(bool visible);

	void setStartRound(bool visible);

	void setCellRound(bool visible);

	void setCardSpeRound(bool visible);
	
	void setPrisonRound(bool visible);

	void setExchangeRound(bool visible);
	
	void setBankruptRound(bool visible);

	void setAuctionRound(bool visible);

	void setSpeRound(bool visible);

	void onlyLeaveRound(bool visible);

	void setJoinAuctionRound(bool visible);

	void setEnd(bool visible);
	
	void hideAllButton();

public:

	explicit GameGUIView(sf::RenderWindow* window);
	
	~GameGUIView()=default;



	void draw() override;

	void drawStartGame();

	void drawStartRound();

	void drawCellRound();

	void drawCardSpeRound();

	void drawPrisonRound();

	void drawExchangeRound();

	void drawBankruptRound();

	void drawSpeRound();

	void drawEnd();

	void drawJoinAuction();

	void clear();
	friend class GameGUIController;


//method for setting the game

	void startTurn();

	void endTurn();

	void setBoardClickMode(bool clickable);


};
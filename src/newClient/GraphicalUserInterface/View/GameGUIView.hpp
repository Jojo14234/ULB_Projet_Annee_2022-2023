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
#include "GameObject/MiniLobbyBox.hpp"

class GameGUIController; // forward declaration

class GameGUIView: public AbstractGUIView {
	bool startingGame = false;
public:
	Board board;
	MiniLobbyBox lobby{ObjectInfo<>(ObjectInfo<>(400, 400,window->getSize().x -400,window->getSize().y - 400))};
	InfoBox info_box{ObjectInfo<>(400, 400,window->getSize().x -400,window->getSize().y - 400)};

	Box button_zone{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };

	ImageButton startgame_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/6*0  ), START_BUTTON};

	ImageButton mortgage_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/6*0  ), MORTGAGE_BUTTON};
	ImageButton unmortgage_button{ObjectInfo<>(200, 100 ,50, window->getSize().y/6 *1 ), UNMORTGAGE_BUTTON};
	ImageButton sell_button{ObjectInfo<>(200, 100 ,50, window->getSize().y/6 *2), SELL_BUTTON};
	ImageButton construct_button{ObjectInfo<>(200, 100 ,50, window->getSize().y/6 * 3), CONSTRUCT_BUTTON};
	ImageButton exchange_button{ObjectInfo<>(200, 100 ,50, window->getSize().y/6 *4), EXCHANGE_BUTTON};
	ImageButton roll_dice_button{ObjectInfo<>(200, 100 ,50, window->getSize().y/6  * 5), ROLLDICE_BUTTON};

	ImageButton buy_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/2*0  ), BUY_BUTTON};
	ImageButton no_buy_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/2*1  ), NOBUY_BUTTON};

	ImageButton draw_card_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/2*0  ), DRAWCARD_BUTTON};
	ImageButton paid_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/2*1 ), PAID_BUTTON};

	ImageButton paid_prison_button{ObjectInfo<>(200, 100 ,50,0 ), PAID_BUTTON};
	ImageButton roll_dice_prison_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*1 ), ROLLDICE_BUTTON};
	ImageButton card_prison_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*2 ), PRISONCARD_BUTTON};

	ImageButton yes_exchange_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*0 ), YES_BUTTON};
	ImageButton no_exchange_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*1 ), NO_BUTTON};

	ImageButton sell_bankrupt_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*0 ), SELL_BUTTON};
	ImageButton give_up_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*1 ), FORFAIT_BUTTON};

	ImageButton leave_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*0) ,LEAVE_BUTTON};

	ImageButton participate_button{ObjectInfo<>(200, 100 ,50,window->getSize().y/3*3) ,PARTICIPATE_BUTTON};
	
	std::vector<std::string> colorlist{"red","blue","green","cyan","magenta","yellow"};   //pour tester à enlever

	AuctionBox auction_box{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };  //boutons enchères

	ExchangeBox exchange_box{ObjectInfo<>(300, window->getSize().y,0,0), sf::Color::Red };

	bool exchange_mode = false;
	bool other_mode = false;

	std::string button_mode = "";
 
	MessageBox message_box{ObjectInfo<>(800,60,350,5)};  //zone en haut qui affiche les actions des joueurs

	GamecodeBox gamecode_box{ObjectInfo<>(400,200,550,200)};

	Dice dice;

	Image logo {ObjectInfo<>(615,200,450,200),LOGO_PATH};
	Image card_zone{ObjectInfo<>(390,300,560,500),CARD_TEXT};
	Text card_text{ObjectInfo<>(0,20,590,600),""};
	Text card_title{ObjectInfo<>(0,34,585,600),"    CHANCE et\nCAISSE DE COMMU"};

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

	void drawJoinAuction();

	void clear();
	friend class GameGUIController;


//method for setting the game

	void startTurn();

	void endTurn();

	void setBoardClickMode(bool clickable);


};
/**
 * Project Untitled
 */

#pragma once

#include <SFML/Window.hpp>

#include "AbstractGUIController.hpp"
#include "SubjectGUIController.hpp"

#include "../configs.hpp"
#include <thread>


#include "../../Model/QueryParser/GameLaunchingParser.hpp"
#include "../../Model/QueryParser/InGameParser.hpp"


class Client; // forward declaration
class GameGUIView; // forward declaration

class GameGUIController: public AbstractGUIController, public SubjectGUIController{

	int player_nb;
	std::vector<std::string> players_username;

	bool init = true;

	std::shared_ptr<JoinInfo> game_info;
	std::vector<std::string> selection_mode;

	GameGUIView* view;

public: 
	
	GameGUIController(Client* model, GameGUIView* view) : AbstractGUIController(model, STATE::GAME), view{view} {}

	~GameGUIController()=default;

	void handle(sf::Event event) override;
	
	void receiveMsgLoop();


	void createGameGU(const std::string& response);
	void joinGameGU(const std::string& response);
	void infoStartGU(const std::string& response);
	void rollDiceGU(const std::string& response);
	void infoGameGU(const std::string& response);
	void newTurnGU(const std::string& response);
	void newTurnInJailGU(const std::string& response);
	void doubleTurnGU(const std::string& response);
	void playerMoveGU(const std::string& response);
	void playerBoughtGU(const std::string& response);
	void playerPaidPlayerGU(const std::string& response);
	void moveOnMortgagedCellGU(const std::string& response);
	void moveOnTaxCellGU(const std::string& response);
	void goOutPrisonGU(const std::string& response);
	void sendPrisonGU(const std::string& response);
	void getGoOutJailCardGU(const std::string& response);
	void loseGoOutJailCardGU(const std::string& response);
	void wonMoneyGU(const std::string& response);
	void loseMoneyGU(const std::string& response);
	void cardCellToGoGU(const std::string& response);
	void moveOnCardCellGU(const std::string& response);
	void drawCardGU(const std::string& response);
	void buildPropertyGU(const std::string& response);
	void sellPropertyGU(const std::string& response);
	void exchangePropertyGU(const std::string& response);
	void mortgagePropertyGU(const std::string& response);
	void unmortgagePropertyGU(const std::string& response);
	void leaveSelectionMenuGU(const std::string& response);
	void buildOrSellSucceedGU(const std::string& response);
	void mortgageSucceedGU(const std::string& response);
	void unmortgageSucceedGU(const std::string& response);
	void exchangeSucceedGU(const std::string& response);
	void askExchangeGU(const std::string& response);
	void confirmExchangeAskingGU(const std::string& response);
	void askForPurchaseGU(const std::string& response);
	void askAuctionGU(const std::string& response);
	void startAuctionGU(const std::string& response);
	void auctionBidGU(const std::string& response);
	void endAuctionGU(const std::string& response);
	void endGameGU(const std::string& response);
	void wonLandGU(const std::string& response);

	void initGame();

	void initScreen(int gamecode);

	void startGame(int beginner);

	void choiceSpeCard();

    //todo add from n-curse
    void playerJoinUpdate();

	void update() override;

	

	// ...

};
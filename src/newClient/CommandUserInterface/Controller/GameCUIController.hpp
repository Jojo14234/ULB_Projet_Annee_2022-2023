#pragma once

#include <vector>
#include "AbstractCUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class GameCUIView; // forward declaration

class GameCUIController: public AbstractCUIController, public MenuCUIObserver {

	enum GAME_STATE { CHAT, CONSOLE, IDLE };
	GAME_STATE state = IDLE;

	GameCUIView* view;
	Subject* win;

	int player_nb;
	bool init = true;
	std::vector<std::string> players_username;
	std::vector<std::string> build_mode;

	//Graphical Updates
	void createGameGU(const std::string& response);
	void joinGameGU(const std::string& response);
	void infoStartGU(const std::string& response);
	void rollDiceGU(const std::string& response);
	void infoGameGU(const std::string& response);
	void newTurnGU(const std::string& response);
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
	void leaveBuildMenuGU(const std::string& response);
	void buildSuceedGU(const std::string& response);
	void askForPurchaseGU(const std::string& response);

public: 
	
	GameCUIController(Client* model, GameCUIView* view);

	~GameCUIController()=default;

	void handle(int event) override;
	
	void move() override;

	void receiveMsgLoop();

	void initGame();

	void initScreen(int gamecode);

	void startGame(int beginner);

    //todo add from n-curse
    void playerJoinUpdate();
    void setSubject(Subject* win) { this->win = win; }

	void update() override;

};
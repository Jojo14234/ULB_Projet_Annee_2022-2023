//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#pragma once
#include <string>
#include "AbstractCLIController.hpp"
#include "../View/GameCLIView.hpp"
#include "../configs.hpp"

class Client; // forward declaration
class GameCLIView; // forward declaration

class GameCLIController : public AbstractCLIController, public MenuCLIObserver {
    int player_number = 0;
    std::vector<std::string> players_usernames;

    GameCLIView* view;

    void createGameGu(const std::string &res);
    void joinGameGU(const std::string &res);
    void infoStartGU(const std::string &res);
    void rollDiceGU(const std::string &res);
    void infoGameGU(const std::string &res);
    void newTurnGU(const std::string &res);
    void playerMoveGU(const std::string &res);
    void playerBoughtGU(const std::string &res);
    void playerDidNotBoughtGU(const std::string &res);
    void playerPaidPlayerGU(const std::string &res);
    void moveOnMortgagedCellGU(const std::string &res);
    void moveOnOwnCellGU(const std::string &res);
    void askForPurchaseGU(const std::string &res);
    void moveOnTaxCellGU(const std::string &res);
    void goOutPrisonGU(const std::string &res);
    void sendPrisonGU(const std::string &res);
    void loseGoOutJailCardGU(const std::string &res);
    void getGoOutJailCardGU(const std::string &res);
    void wonMoneyGU(const std::string &res);
    void loseMoneyGU(const std::string &res);
    void moveOnCardCellGU(const std::string &res);
    void drawCardGU(const std::string &res);
    void buildPropertyGU(const std::string &res);
    void sellPropertyGU(const std::string &res);
    void leaveBuildMenuGU(const std::string &res);
    void buildSucceedGU(const std::string &res);
    void notEnoughMoneyGU(const std::string &res);
    void choiceMoneyCardGU(const std::string &res);
    void cannotBuildGu(const std::string &res);
    void NotBuildableProp(const std::string &res);




public:

    GameCLIController(Client* model, GameCLIView* view);

    ~GameCLIController()=default;

    void handle(int event) override;

    void receiveMsgLoop();

    void initGame();

    void update() override;

    void interruptWait();

};


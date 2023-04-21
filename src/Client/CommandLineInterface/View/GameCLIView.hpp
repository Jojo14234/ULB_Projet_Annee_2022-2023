#pragma once

#include "AbstractCLIView.hpp"
#include "../../../Utils/AccessMonitor.hpp"
#include "../../Model/Client.hpp"
#include "../../Model/QueryParser/GameLaunchingParser.hpp"
#include "../../Model/QueryParser/InGameParser.hpp"


class GameCLIView : public  AbstractCLIView {
public:
    GameCLIView() : AbstractCLIView() {};

    ~GameCLIView() = default;

    void draw() override;

    void createGame(JoinInfo2 &info);
    void joinGame(JoinInfo2 &info);
    void startInfo(StartInfo2 &info);
    void rollInfo(RollDiceInfo2 &info);

    void infosGame(GameInfoList &info);
    void newTurn(std::string username);
    void moveOn(PlayerMoveInfo2 &info);
    void buyProp(PlayerMoveInfo2 &info);
    void didntBuy(std::string username);
    void playerPaidPlayer(PlayerPaidPlayerInfo2 &info);
    void mortgagedCellMoveOn(MoveMortgagedInfo2 &info);
    void ownCellMoveOn(std::string username);
    void taxCellMoveOn(MoveTaxInfo2 &info);
    void askPurchase(AskForPurchaseInfo2 &info);
    void getInJail(std::string username);
    void getOutJail(std::string username);

    void getOutJailCard(std::string username);
    void UseOutJailCard(std::string username);

    void gainMoney(WonOrLoseMoneyInfo2 &info);
    void looseMoney(WonOrLoseMoneyInfo2 &info);

    void drawCardMoveOn(MoveOnCardCellInfo2 &info);
    void drawCardMoveOn(std::string description);

    void joinBuildMode(BuildOrSellList &info);
    void joinSellMode(BuildOrSellList &info);

    void leaveMode();

    void propInfos(BuildSuccessInfo2 &info);

    void notEnoughMoney();

    void cannotBuild();
    void dontHavePropBuildable();

    void choiceMoneyCard();
};

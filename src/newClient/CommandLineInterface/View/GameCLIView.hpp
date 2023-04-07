#pragma once

#include "AbstractCLIView.hpp"
#include "../../../utils/AccessMonitor.hpp"
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
};

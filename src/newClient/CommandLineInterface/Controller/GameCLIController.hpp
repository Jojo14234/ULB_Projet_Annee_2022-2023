//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#pragma once

#include "AbstractCLIController.hpp"
#include "../configs.hpp"

class Client; // forward declaration
class GameCLIView; // forward declaration

class GameCLIController : public AbstractCLIController, public MenuCLIObserver {

    GameCLIView* view;

public:

    GameCLIController(Client* model, GameCLIView* view);

    ~GameCLIController()=default;

    void handle(int event) override;

    void receiveMsgLoop();

    void initGame();

    void update() override;

};


//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#pragma once

#include "AbstractCLIController.hpp"
#include "../configs.hpp"

class Client; // forward declaration
class GameCLIView; // forward declaration

class GameCLIController : public AbstractCLIController, public MenuCLIObserver {

public:

    GameCLIController(Client* model);

    ~GameCLIController()=default;

    void handle(int event) override;

    void receiveMsgLoop();

    void initGame();

    void update() override;

};


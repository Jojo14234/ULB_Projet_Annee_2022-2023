//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#pragma once

#include "AbstractCLIController.hpp"
#include "../configs.hpp"

class Client; // forward declaration

class MenuCLIController : public AbstractCLIController, public GameCLISubject {

public:

    MenuCLIController(Client* model, MenuCLIObserver* subject);

    ~MenuCLIController()=default;

    void handle(int event) override;

    void handleRankingPos(std::string &input);

    void handleRankingTop(std::string &input);


};


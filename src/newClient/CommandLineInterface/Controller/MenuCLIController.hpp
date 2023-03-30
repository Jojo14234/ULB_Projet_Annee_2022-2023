//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#pragma once

#include "AbstractCLIController.hpp"
#include "../configs.hpp"

class Client; // forward declaration
class MenuCLIView; // forward declaration

class MenuCLIController : public AbstractCLIController, public GameCLISubject {

    MenuCLIView* view;

public:

    MenuCLIController(Client* model, MenuCLIView* view, MenuCLIObserver* subject);

    ~MenuCLIController()=default;

    void handle(int event) override;

    void move() override;

};


#pragma once

#include "AbstractCLIView.hpp"
#include "../../../utils/AccessMonitor.hpp"
#include "../../Model/Client.hpp"


class GameCLIView : public  AbstractCLIView {
public:
    GameCLIView() : AbstractCLIView() {};

    ~GameCLIView()=default;

    void draw() override;

    void draw2();
};

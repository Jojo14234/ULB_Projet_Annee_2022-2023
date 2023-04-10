//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#pragma once

#include "AbstractCLIView.hpp"


class ConnectionCLIView : public AbstractCLIView {

public:
    ConnectionCLIView()=default;

    ~ConnectionCLIView()=default;

    void draw() override;

    void draw2();

};


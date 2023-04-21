#pragma once

#include "AbstractCLIView.hpp"

class MenuCLIView : public AbstractCLIView {

public:
    MenuCLIView()=default;

    ~MenuCLIView()=default;

    void draw() override;
};

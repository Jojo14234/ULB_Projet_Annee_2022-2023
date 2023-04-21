#pragma once

#include "../../View/AbstractView.hpp"
#include "../AbstractCLI.hpp"
#include "../../Model/Client.hpp"


class AbstractCLIView: public AbstractView, public AbstractCLI {

public:

    AbstractCLIView(): AbstractView(), AbstractCLI() {}

    virtual ~AbstractCLIView()=default;

    virtual void draw()=0;

};


//
// Created by Rémy Ryckeboer on 29/03/2023.
//

#ifndef INFO_F209_GR5_2022_ABSTRACTCLICONTROLLER_HPP
#define INFO_F209_GR5_2022_ABSTRACTCLICONTROLLER_HPP


#include "../../Controller/AbstractController.hpp"
#include "../AbstractCUI.hpp"
#include "../configs.hpp"


class AbstractCUIController: public AbstractController<STATE, int>, public AbstractCUI {

public:

    using AbstractController<STATE, int>::AbstractController;

    virtual ~AbstractCUIController()=default;

    virtual void handle(int event) override = 0;

    virtual void move()=0;

};

#endif //INFO_F209_GR5_2022_ABSTRACTCLICONTROLLER_HPP

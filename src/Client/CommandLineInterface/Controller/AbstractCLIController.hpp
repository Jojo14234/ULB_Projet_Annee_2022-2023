//
// Created by Rémy Ryckeboer on 29/03/2023.
//

#ifndef INFO_F209_GR5_2022_ABSTRACTCLICONTROLLER_HPP
#define INFO_F209_GR5_2022_ABSTRACTCLICONTROLLER_HPP


#include "../../Controller/AbstractController.hpp"
#include "../AbstractCLI.hpp"
#include "../configs.hpp"


class AbstractCLIController: public AbstractController<STATE, int>, public AbstractCLI {

public:

    using AbstractController<STATE, int>::AbstractController;

    virtual ~AbstractCLIController()=default;

    virtual void handle(int event) override = 0;

    void move() override {}

};

#endif //INFO_F209_GR5_2022_ABSTRACTCLICONTROLLER_HPP

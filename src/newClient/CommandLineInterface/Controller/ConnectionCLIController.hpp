//
// Created by Rémy Ryckeboer on 29/03/2023.
//

#ifndef INFO_F209_GR5_2022_CONNECTIONCLICONTROLLER_HPP
#define INFO_F209_GR5_2022_CONNECTIONCLICONTROLLER_HPP


#include "AbstractCLIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration

class ConnectionCLIController: public AbstractCLIController {

public:

    ConnectionCLIController(Client* model);

    ~ConnectionCLIController()=default;

    void handle(int event) override;

};


#endif //INFO_F209_GR5_2022_CONNECTIONCLICONTROLLER_HPP

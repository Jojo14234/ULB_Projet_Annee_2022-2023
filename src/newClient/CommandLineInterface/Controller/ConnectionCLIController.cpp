//
// Created by Rémy Ryckeboer on 29/03/2023.
//

#include <iostream>
#include <string>

#include "ConnectionCLIController.hpp"
#include "../../Model/InputParser/ConnectionInputParser.hpp"
#include "../../Model/Client.hpp"


ConnectionCLIController::ConnectionCLIController(Client *model)
        : AbstractCLIController{model, STATE::CONNECTION} {};

//todo
void ConnectionCLIController::handle(int event) {
    if (event) {} // to use the param

    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    ConnectionInputParser parser{input};

    switch (parser.getQuery()) {
        case CONNECTION_QUERY::LOGIN :      this->model->sendLogin(parser[1], parser[2]); break;
        case CONNECTION_QUERY::REGISTER :   this->model->sendRegister(parser[1], parser[2]); break;
        case CONNECTION_QUERY::DISCONNECT:  this->model->sendDisconnect(); break;
        default: break;
    }

    if (parser.getQuery() != CONNECTION_QUERY::OTHER) {
        std::string response;
        QUERY query = this->model->receive(response);
        if ( query == QUERY::TRUEQ ) { this->new_state = STATE::MENU; }
        else if ( query == QUERY::DISCONNECT ) { exit(0); }
    }
}

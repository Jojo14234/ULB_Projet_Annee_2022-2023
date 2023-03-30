//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#include "MenuCLIController.hpp"
#include "../View/MenuCLIView.hpp"
#include "../../Model/InputParser/MainInputParser.hpp"


MenuCLIController::MenuCLIController(Client *model, MenuCLIView *view)
        : AbstractCLIController(model, STATE::MENU), view{view} {};

void MenuCLIController::handle(int event) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    MainInputParser parser{input};

    switch (parser.getQuery()) {

        case QUERY_TYPE::RANKING_POS :
        case QUERY_TYPE::RANKING_TOP : this->model->sendCommand(parser); break;
        default : break;
    }

    if (parser.getQuery() != QUERY_TYPE::NONE) {
        std::string response;
        QUERY query = this->model->receive(response);
        std::cout << response << std::endl;
    }

}


//todo
void MenuCLIController::move() {

}
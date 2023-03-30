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
        //todo ici voir si le switch est obligatoire
        case QUERY_TYPE::FRIENDS_LIST :
        case QUERY_TYPE::RANKING_POS :
        case QUERY_TYPE::RANKING_TOP :
        default : this->model->sendCommand(parser);
    }

    if (parser.getQuery() != QUERY_TYPE::NONE) {
        std::string response;
        QUERY query = this->model->receive(response);
        std::cout << (int)query << std::endl;
        if ( query == QUERY::DISCONNECT ) { this->new_state = STATE::CONNECTION; }
        else { std::cout << response << std::endl; } //todo ici utilisé la vue
    }
    else { this->new_state = STATE::MENU; }

}


//todo
void MenuCLIController::move() {

}
//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#include "MenuCLIController.hpp"
#include "../View/MenuCLIView.hpp"
#include "../../Model/InputParser/MainInputParser.hpp"


MenuCLIController::MenuCLIController(Client *model, MenuCLIView *view, MenuCLIObserver* subject)
        : AbstractCLIController{model, STATE::MENU}, GameCLISubject{subject}, view{view} {};

void MenuCLIController::handle(int event) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    MainInputParser parser{input};

    switch (parser.getQuery()) {
        //todo ici voir si le switch est obligatoire
        case QUERY_TYPE::JOIN_GAME :
        case QUERY_TYPE::CREATE_GAME :
        default : this->model->sendCommand(parser);
    }

    if (parser.getQuery() != QUERY_TYPE::NONE) {
        std::string response;
        QUERY query = this->model->receive(response);
        if ( query == QUERY::DISCONNECT ) { this->new_state = STATE::CONNECTION; }
        else if ( query == QUERY::PLAYER_CREATE_GAME ) { this->new_state = STATE::GAME; this->notify(); std::cout << response << std::endl; }
        else if ( query == QUERY::PLAYER_JOIN_GAME ) { this->new_state = STATE::GAME; this->notify(); }
        else { std::cout << response << std::endl; } //todo ici utilisé la vue
    }
    else { this->new_state = STATE::MENU; }

}


//todo
void MenuCLIController::move() {

}
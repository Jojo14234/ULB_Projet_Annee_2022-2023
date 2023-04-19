//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#include "MenuCLIController.hpp"
#include "../View/MenuCLIView.hpp"
#include "../../Model/InputParser/MainInputParser.hpp"
#include "../../Model/QueryParser/MenuParser.hpp"


MenuCLIController::MenuCLIController(Client *model, MenuCLIObserver* subject)
        : AbstractCLIController{model, STATE::MENU}, GameCLISubject{subject} {};

void MenuCLIController::handle(int event) {
    if (event) {} // to use the param

    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    MainInputParser parser{input};

    switch (parser.getQuery()) {
        //todo ici voir si le switch est obligatoire
        case QUERY_TYPE::JOIN_GAME : this->model->sendJoinGame(std::stoi(parser[1])); break;
        default : this->model->sendCommand(parser);
    }

    if (parser.getQuery() != QUERY_TYPE::NONE) {
        std::string response;
        QUERY query = this->model->receive(response);
        if ( query == QUERY::DISCONNECT ) { this->new_state = STATE::CONNECTION; }
        else if ( query == QUERY::PLAYER_CREATE_GAME ) { this->new_state = STATE::GAME; this->notify(); std::cout << response << std::endl; }
        else if ( query == QUERY::PLAYER_JOIN_GAME ) { this->new_state = STATE::GAME; this->notify(); }
        else if ( query == QUERY::RANKING_POS) { this->handleRankingPos(response); }
        else if ( query == QUERY::RANKING_TOP) { this->handleRankingPos(response); }
        else { std::cout << response << std::endl; } //todo ici utilisé la vue
    }
    else { this->new_state = STATE::MENU; }

}

void MenuCLIController::handleRankingPos(std::string &input) {
    RankingINFO info{input};
    std::cout << "Le joueur " << info.username << " classé à la " << info.pos << "em position avec " << info.points << " point(s)." << std::endl;
}   

void MenuCLIController::handleRankingTop(std::string &input) {
    RankingInfosList ranking{input};

    for (auto rank : ranking.infos) {
    std::cout << "Le joueur " << rank.username << " classé à la " << rank.pos << "em position avec " << rank.points << " point(s)." << std::endl;
    }
}

//
// Created by Rémy Ryckeboer on 30/03/2023.
//
#include <thread>


#include "GameCLIController.hpp"

#include "../View/GameCLIView.hpp"
#include "../../Model/InputParser/GameInputParser.hpp"


GameCLIController::GameCLIController(Client *model, GameCLIView *view)
        : AbstractCLIController{model, STATE::GAME}, view{view} {};


void GameCLIController::handle(int event) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    GameInputParser parser{input};

    switch (parser.getQuery()) {
        // todo virer le switch
        default : this->model->sendCommand(parser);
    }

    if ( parser.getQuery() != GAME_QUERY_TYPE::NONE ) {
        std::string response;
        QUERY query = this->model->receive(response);
        std::cout << response << std::endl;
    }
    else { this->new_state = STATE::GAME; }
}

void GameCLIController::initGame() {
    // create a thread to receive messages
    std::thread send_thread(&GameCLIController::receiveMsgLoop, this);
    send_thread.detach(); // todo dmd a Hugo c'est quoi le .detach
    //send_thread.join();
}

void GameCLIController::receiveMsgLoop() {
    while (this->new_state == STATE::GAME) {
        std::string response;
        QUERY query = this->model->receive(response);

        switch (query) {
            case QUERY::INFOS_START : break;
            case QUERY::PLAYER_JOIN_GAME : break;
            case QUERY::INFOS_ROLL_DICE : break;
            case QUERY::INFOS_GAME : break;
            case QUERY::INFOS_NEW_TURN : break;
            case QUERY::INFOS_PLAYER_MOVE : break;
            case QUERY::INFOS_PLAYER_BOUGHT : break;
            case QUERY::INFOS_PLAYER_DIDNT_BUY : break;
            case QUERY::INFOS_PLAYER_PAID_PLAYER : break;
            case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL : break;
            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL : break;
            case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL : break;
            case QUERY::INFOS_PLAYER_GO_OUT_PRISON : break;
            case QUERY::INFOS_PLAYER_SEND_TO_PRISON : break;
            case QUERY::GET_GO_OUT_JAIL_CARD : break;
            case QUERY::LOST_GO_OUT_JAIL_CARD : break;
            case QUERY::INFOS_PLAYER_WON_MONEY : break;
            case QUERY::INFOS_PLAYER_LOSE_MONEY : break;
            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL : break;
            case QUERY::INFOS_CARD_DESCRIPTION : break;
            case QUERY::CHOICE_MONEY_CARD : break;
            case QUERY::USELESS_MESSAGE : break;
            case QUERY::INFOS_BUILD_PROP : break;
            case QUERY::INFOS_SELL_BUILD : break;
            case QUERY::INFOS_LEAVE_BUILD_MODE : break;
            case QUERY::INFOS_ASK_FOR_PURCHASE : break;
            case QUERY::INFOS_NOT_ENOUGH_MONEY : break;
            case QUERY::STOP_WAIT : this->model->sendCommand(GameInputParser{response}); break;
            case QUERY::ENDGAME : this->new_state = STATE::MENU; break; // todo verifier
            default : break;
        }
    }
}

//todo
void GameCLIController::update() {

}
//todo
void GameCLIController::move() {

}
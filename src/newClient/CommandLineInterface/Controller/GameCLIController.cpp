//
// Created by Rémy Ryckeboer on 30/03/2023.
//
#include <thread>


#include "GameCLIController.hpp"

#include "../View/GameCLIView.hpp"
#include "../../Model/InputParser/GameInputParser.hpp"
#include "../../Model/QueryParser/GameLaunchingParser.hpp"
#include "../../Model/QueryParser/InGameParser.hpp"


GameCLIController::GameCLIController(Client *model, GameCLIView* view)
        : AbstractCLIController{model, STATE::GAME}, view{view} {};


void GameCLIController::handle(int event) {
    if (event) {} // to use the param

    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    GameInputParser parser{input};

    if ( parser.getQuery() != GAME_QUERY_TYPE::NONE ) { this->model->sendCommand(parser); }

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
            case QUERY::PLAYER_CREATE_GAME :        createGameGu(response); break;
            case QUERY::PLAYER_JOIN_GAME :          joinGameGU(response); break;
            case QUERY::INFOS_START :               infoStartGU(response); break;
            case QUERY::INFOS_ROLL_DICE :           rollDiceGU(response); break;
            case QUERY::INFOS_GAME :                infoGameGU(response); break;
            case QUERY::INFOS_NEW_TURN :            newTurnGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE :         playerMoveGU(response); break;
            case QUERY::INFOS_PLAYER_BOUGHT :       playerBoughtGU(response); break;
            case QUERY::INFOS_PLAYER_DIDNT_BUY :    playerDidNotBoughtGU(response); break;
            case QUERY::INFOS_PLAYER_PAID_PLAYER :  playerPaidPlayerGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL : moveOnMortgagedCellGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL : moveOnOwnCellGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL : moveOnTaxCellGU(response); break;
            case QUERY::INFOS_PLAYER_GO_OUT_PRISON :    goOutPrisonGU(response); break;
            case QUERY::INFOS_PLAYER_SEND_TO_PRISON :   sendPrisonGU(response); break;
            case QUERY::GET_GO_OUT_JAIL_CARD :      getGoOutJailCardGU(response); break;
            case QUERY::LOST_GO_OUT_JAIL_CARD :     loseGoOutJailCardGU(response); break;
            case QUERY::INFOS_PLAYER_WON_MONEY :    wonMoneyGU(response); break;
            case QUERY::INFOS_PLAYER_LOSE_MONEY :   loseMoneyGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL : moveOnCardCellGU(response); break;
            case QUERY::INFOS_CARD_DESCRIPTION :    drawCardGU(response); break;
            case QUERY::USELESS_MESSAGE :           std::cout << response << std::endl; break;
            case QUERY::MESSAGE :                   std::cout << response << std::endl; break;
            case QUERY::CHOICE_MONEY_CARD :         choiceMoneyCardGU(response);break;
            case QUERY::INFOS_BUILD_PROP :          buildPropertyGU(response); break;
            case QUERY::INFOS_SELL_BUILD :          sellPropertyGU(response); break;
            case QUERY::INFOS_LEAVE_SELECTION_MODE :    leaveBuildMenuGU(response); break;
            case QUERY::INFOS_ASK_FOR_PURCHASE :    askForPurchaseGU(response); break;
            case QUERY::INFOS_BUILD_SUCCESS :       buildSucceedGU(response); break;
            case QUERY::CANNOT_BUILD :              cannotBuildGu(response); break;
            case QUERY::NO_BUILDABLE_PROP :         NotBuildableProp(response); break;

            case QUERY::INFOS_NOT_ENOUGH_MONEY :    notEnoughMoneyGU(response); break;
            case QUERY::STOP_WAIT :                 this->model->sendCommand(GameInputParser{response}); break;
            case QUERY::ENDGAME :                   this->new_state = STATE::MENU; break; // todo verifier
            default : break;
        }
    }
}

void GameCLIController::update() {
    this->initGame();
}


void GameCLIController::createGameGu(const std::string &res) {
    JoinInfo2 info{res, true};
    this->player_number = info.nb_player;
    this->players_usernames = info.player_usernames;
    this->view->createGame(info);
    this->view->joinGame(info);
}

void GameCLIController::joinGameGU(const std::string &res) {
    JoinInfo2 info{res, false};
    this->player_number = info.nb_player;
    this->players_usernames = info.player_usernames;
    this->view->joinGame(info);
}

void GameCLIController::infoStartGU(const std::string &res) {
    StartInfo2 info{res};
    this->player_number = info.player_nb;
    this->players_usernames = info.player_usernames;
    this->view->startInfo(info);
}

void GameCLIController::rollDiceGU(const std::string &res) {
    RollDiceInfo2 info{res};
    this->view->rollInfo(info);
}

void GameCLIController::infoGameGU(const std::string &res) {
    GameInfoList infos{res};

    // view afficher les infos du tour
    this->view->infosGame(infos);

    //todo debuger
    InGameParser parser{res};
    std::shared_ptr<std::vector<GameInfo>> infos2 = parser.parseInfosGameQuery(this->player_number);
}

void GameCLIController::newTurnGU(const std::string &res) {
    // afficher le pseudo du joueur à qui c'est le tour
    // res = pseudo
    this->view->newTurn(res);
}

void GameCLIController::playerMoveGU(const std::string &res) {
    PlayerMoveInfo2 info{res};
    // view afficher le nom de la case
    this->view->moveOn(info);
}

void GameCLIController::playerBoughtGU(const std::string &res) {
    PlayerMoveInfo2 info{res};
    //view afficher que la propriété vient d'être acheté par le joueur
    this->view->buyProp(info);
}

void GameCLIController::playerDidNotBoughtGU(const std::string &res) {
    // view afficher le [res] n'a pas acheter la propriété
    this->view->didntBuy(res);
}

void GameCLIController::playerPaidPlayerGU(const std::string &res) {
    PlayerPaidPlayerInfo2 info{res};
    //afficher qui doit quoi à qui
    this->view->playerPaidPlayer(info);
}

void GameCLIController::moveOnMortgagedCellGU(const std::string &res) {
    MoveMortgagedInfo2 info{res};
    // view [machin] est tombé sur une propriéte hypothéqué
    this->view->mortgagedCellMoveOn(info);
}

void GameCLIController::moveOnOwnCellGU(const std::string &res) {
    // view afficher [machin] est chez lui
    this->view->ownCellMoveOn(res);
}

void GameCLIController::moveOnTaxCellGU(const std::string &res) {
    MoveTaxInfo2 info{res};
    // View vous arrivez sur la case [nom] et vous payer [prix] de taxe
    this->view->taxCellMoveOn(info);
}

void GameCLIController::askForPurchaseGU(const std::string &res) {
    AskForPurchaseInfo2 info{res};
    //view afficher acheter [case] pour [prix]
    // /yes /no
    // si no enchère
    this->view->askPurchase(info);
}

void GameCLIController::goOutPrisonGU(const std::string &res) {
    // [machin] sort de prison
    this->view->getOutJail(res);
}

void GameCLIController::sendPrisonGU(const std::string &res) {
    // [machin] va en prison
    this->view->getInJail(res);
}

void GameCLIController::getGoOutJailCardGU(const std::string &res) {
    // [machin] obtient une carte sortie de prison
    this->view->getOutJailCard(res);
}

void GameCLIController::loseGoOutJailCardGU(const std::string &res) {
    // [machin] utilise une carte sortie de prison
    this->view->UseOutJailCard(res);
}

void GameCLIController::wonMoneyGU(const std::string &res) {
    WonOrLoseMoneyInfo2 info{res};
    // vous gagnez ... €
    this->view->gainMoney(info);
}

void GameCLIController::loseMoneyGU(const std::string &res) {
    WonOrLoseMoneyInfo2 info{res};
    // vous perdez ... €
    this->view->looseMoney(info);
}

void GameCLIController::moveOnCardCellGU(const std::string &res) {
    MoveOnCardCellInfo2 info{res};
    // vous avez piochez la carte
    // description
    this->view->drawCardMoveOn(info);
}

void GameCLIController::drawCardGU(const std::string &res) {
    // vous venez de piochez une carte
    // [response]
    this->view->drawCardMoveOn(res);
}

void GameCLIController::buildPropertyGU(const std::string &res) {
    BuildOrSellList info{res};
    // view /select [nom] pour construire
    // /leave pour quitter.
    // Afficher les propriétés possibles
    this->view->joinBuildMode(info);
}

void GameCLIController::sellPropertyGU(const std::string &res) {
    BuildOrSellList info{res};
    // view /select [nom] pour vendre
    // /leave pour quittez
    // affichez les porpiété possible
    this->view->joinSellMode(info);
}

void GameCLIController::leaveBuildMenuGU(const std::string &res) {
    // view vous avez quittez le menu de selection
    this->view->leaveMode();
}

void GameCLIController::buildSucceedGU(const std::string &res) {
   BuildSuccessInfo2 info{res};
   // la propriété ... est de niveau ...
   this->view->propInfos(info);
}

void GameCLIController::notEnoughMoneyGU(const std::string &res) {
    // Vous n'avez pas assez d'argent
    this->view->notEnoughMoney();
}

void GameCLIController::choiceMoneyCardGU(const std::string &res) {
    //view /pay ou /card
    this->view->choiceMoneyCard();
}

void GameCLIController::cannotBuildGu(const std::string &res) {
    // "Ce terrain ne peut pas acceuillir de nouveaux batiments"
    this->view->cannotBuild();
}

void GameCLIController::NotBuildableProp(const std::string &res) {
    // "Vous n\'avez pas de terrain pouvant avoir de nouveaux batiments")
    this->view->dontHavePropBuildable();
}
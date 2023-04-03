#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>
#include <string>
#include <memory>

#include "GameCUIController.hpp"
#include "../View/GameCUIView.hpp"
#include "../../Model/QueryParser/GameLaunchingParser.hpp"
#include "../../Model/QueryParser/InGameParser.hpp"


// Public

GameCUIController::GameCUIController(Client* model, GameCUIView* view) :
	AbstractCUIController(model, STATE::GAME), view{view} {};

// todo added from n-curse
void GameCUIController::handle(int ch) {
    switch(ch) {
        case KEY_MOUSE:
            MEVENT event;
            if (getmouse(&event) != OK) { break; }
            if (event.bstate & BUTTON1_CLICKED) {
                if ( this->view->getConsole()->isClicked(Position{event.x, event.y}) ) { this->state = CONSOLE; }
                else if ( this->view->getChat()->isClicked(Position{event.x, event.y}) ) { this->state = CHAT; }
                else { this->state = IDLE; }
            } break;

        case '\n':
            switch(this->state) {
                case CONSOLE: {
                    this->view->getConsole()->addInput();
                    GameInputParser parser(this->view->getConsole()->getInput());
                    if ( not this->model->sendCommand(parser)) this->view->getConsole()->addText("La commande n'existe pas");
                    break; }

                case CHAT: {
                    this->view->getChat()->addInput();
                    MainInputParser parser(this->view->getChat()->getInput());
                    if (not this->model->sendCommand(parser)) this->view->getChat()->addText("La commande n'existe pas");
                    break; }

                case IDLE: break;
            } break;

        default:
            switch (this->state) {
                case CONSOLE: this->view->getConsole()->handleInput(ch); break;
                case CHAT: this->view->getChat()->handleInput(ch); break;
                case IDLE: break;
            } break;
    }
}

// todo added from n-curse
void GameCUIController::move() {
    switch (this->state) {
        case CHAT: this->view->getChat()->move(); break;
        case CONSOLE: this->view->getConsole()->move(); break;
        case IDLE: break;
    }
}

void GameCUIController::receiveMsgLoop() {
    while (this->new_state == STATE::GAME) {
        std::string response;
        QUERY cury = this->model->receive(response);

        switch(cury) {
            case QUERY::PLAYER_CREATE_GAME:{
                GameLaunchingParser launching_parser(response);
                std::shared_ptr<JoinInfo> join_info = launching_parser.parseCreateQuery();
                player_nb = join_info->nb_player;
                players_username = join_info->player_usernames;
                this->initScreen(join_info->game_code);
                this->playerJoinUpdate();
                break;
            }

            case QUERY::PLAYER_JOIN_GAME:{
                GameLaunchingParser launching_parser(response);
                std::shared_ptr<JoinInfo> join_info = launching_parser.parseJoinQuery();
                player_nb = join_info->nb_player;
                players_username = join_info->player_usernames;
                this->initScreen(join_info->game_code);
                this->playerJoinUpdate();
                break;
            }

            case QUERY::INFOS_START: {
                GameLaunchingParser launching_parser(response);
                std::shared_ptr<StartInfo> start_info = launching_parser.parseStartQuery();
                player_nb = start_info->player_nb;
                players_username = start_info->player_usernames;
                this->startGame(start_info->beginner);
                this->view->getConsole()->addText("La partie commence");
                break;
            }

            case QUERY::INFOS_ROLL_DICE: {
                InGameParser game_parser(response);
                std::shared_ptr<RollDiceInfo> dice_info = game_parser.parseRollDiceQuery();
                if (this->model->isMyTurn()) {
                    this->view->getDice1()->setText(std::to_string(dice_info->first_value), 0);
                    this->view->getDice2()->setText(std::to_string(dice_info->second_value), 0);
                }  else this->view->getConsole()->addText("Le joueur " + this->model->getPlayerTurn() + " a obtenu un " + std::to_string(dice_info->first_value ) + " et un " + std::to_string(dice_info->second_value));
                break;
            }

            case QUERY::INFOS_GAME: {
                InGameParser game_parser(response);
                std::shared_ptr<std::vector<GameInfo>> player_game_info = game_parser.parseInfosGameQuery(player_nb);
                for (int i = 0; i < player_nb; i++){
                    this->view->getBoard()->movePlayer(player_game_info->at(i).position, i+1);
                    for (unsigned int j = 0; j < player_game_info->at(i).properties.size(); j++){
                        int index = this->view->getBoard()->getCellIndex(player_game_info->at(i).properties[j].name);
                        if (player_game_info->at(i).properties[j].level == 0){
                            this->view->getBoard()->setPurchased(index, i+1);
                        }
                        else this->view->getBoard()->setHouse(index, 2);
                    }

                    this->view->getInfo()->setPlayerInfo(i+1, player_game_info->at(i).money, player_game_info->at(i).jail_card_nb);
                }
                break;
            }

            case QUERY::INFOS_NEW_TURN: {
                this->model->setPlayerTurn(response);
                if (response == this->model->getUsername()) { this->view->startTurn(); this->model->startTurn(); }
                else { this->view->endTurn(); this->model->endTurn(); this->view->getConsole()->addText("C'est au tour de " + response + " !"); }
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE: {
                InGameParser game_parser(response);
                std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
                int index = this->view->getBoard()->getCellIndex(move_info->property_name);
                this->view->getBoard()->movePlayer(index, move_info->player);
                break;
            }

            case QUERY::INFOS_PLAYER_BOUGHT: {
                InGameParser game_parser(response);
                std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
                int index = this->view->getBoard()->getCellIndex(move_info->property_name);
                this->view->getBoard()->setPurchased(index, move_info->player);
                this->view->getInfo()->changePlayerMoney(move_info->player, move_info->player_money);
                break;
            }

            case QUERY::INFOS_PLAYER_DIDNT_BUY: {
                if(response != this->model->getUsername()) this->view->getConsole()->addText("Le joueur " + response + " n'a pas achete la propriete");
                break;
            }

                // TODO AJOUTER VISUELLE POUR DIRE QUAND UNE PERSONNE A ACHETÉ UNE MAISON/VENDRE + HOTEL

            case QUERY::INFOS_PLAYER_PAID_PLAYER:{
                InGameParser game_parser(response);
                std::shared_ptr<PlayerPaidPlayerInfo> payement_info = game_parser.parsePlayerPaidPlayerQuery();
                if (this->model->isMyTurn()) {
                    this->view->getInfo()->changePlayerMoney(payement_info->loser, payement_info->loser_money);
                    this->view->getInfo()->changePlayerMoney(payement_info->winner, payement_info->winner_money);
                    this->view->getConsole()->addText("Vous devez " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
                } else {
                    this->view->getConsole()->addText(players_username[payement_info->loser-1] + " doit " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
                }
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL:{
                InGameParser game_parser(response);
                std::shared_ptr<MoveMortgagedInfo> mortgaged_info = game_parser.parseMoveMortgagedQuery();
                this->view->getConsole()->addText(mortgaged_info->username + " est tombe sur une propriete hypotheque");
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL:{
                if (this->model->isMyTurn()) this->view->getConsole()->addText("Vous etes chez vous.");
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL:{
                InGameParser game_parser(response);
                std::shared_ptr<MoveTaxInfo> tax_info = game_parser.parseMoveTaxQuery();
                int index = this->view->getBoard()->getCellIndex(tax_info->tax_name);
                this->view->getBoard()->movePlayer(index, tax_info->player);
                this->view->getInfo()->changePlayerMoney(tax_info->player, tax_info->player_money);

                if (this->model->isMyTurn()) {
                    this->view->getConsole()->addText("Vous arrivez sur la case " + tax_info->tax_name + " :");
                } else {
                    this->view->getConsole()->addText(players_username[tax_info->player-1] + " paie ses taxes : ");
                }
                break;
            }

            case QUERY::INFOS_PLAYER_GO_OUT_PRISON:{
                if (this->model->isMyTurn()){
                    this->view->getConsole()->addText("Vous sortez de prison.");
                } else this->view->getConsole()->addText(response + "sort de prison.");
                break;
            }

            case QUERY::INFOS_PLAYER_SEND_TO_PRISON:{
                if (this->model->isMyTurn()){
                    this->view->getConsole()->addText("Vous etes envoye en prison.");
                } else this->view->getConsole()->addText(response + " a ete envoye en prison.");
                break;
            }

            case QUERY::GET_GO_OUT_JAIL_CARD:{
                this->view->getInfo()->addCardToPlayer(atoi(response.c_str()));
                if (this->model->isMyTurn()){
                    this->view->getConsole()->addText("Vous obtenez une carte sortie de prison.");
                } else this->view->getConsole()->addText(players_username[atoi(response.c_str()-1)] + "a obtenu une carte sortie de prison.");
                break;
            }

            case QUERY::LOST_GO_OUT_JAIL_CARD:{
                this->view->getInfo()->removeCardToPlayer(atoi(response.c_str()));
                if (this->model->isMyTurn()) this->view->getConsole()->addText("Vous utilisez votre carte.");
                break;
            }

            case QUERY::INFOS_PLAYER_WON_MONEY:{
                InGameParser game_parser(response);
                std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
                this->view->getInfo()->changePlayerMoney(money_info->player, money_info->player_money);
                if (! this->model->isMyTurn()) { this->view->getConsole()->addText(players_username[money_info->player-1] + " a gagne " + std::to_string(money_info->amount) + "$"); }
                else { 
                    if (players_username[money_info->player-1] == this->model->getUsername()){
                        this->view->getConsole()->addText("Vous gagnez " + std::to_string(money_info->amount) + "$");
                    }
                    else this->view->getConsole()->addText(players_username[money_info->player-1] + " gagne " + std::to_string(money_info->amount) + "$");
                }
                break;

            }

            case QUERY::INFOS_PLAYER_LOSE_MONEY:{
                InGameParser game_parser(response);
                std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
                this->view->getInfo()->changePlayerMoney(money_info->player, money_info->player_money);
                if (! this->model->isMyTurn()) this->view->getConsole()->addText(players_username[money_info->player-1] + " a perdu " + std::to_string(-money_info->amount) + "$");
                else { 
                    if (players_username[money_info->player-1] == this->model->getUsername()){
                        this->view->getConsole()->addText("Vous perdez " + std::to_string(money_info->amount) + "$"); 
                    }
                    else this->view->getConsole()->addText(players_username[money_info->player-1] + " perd " + std::to_string(money_info->amount) + "$");
                }
                break;
            }

            case QUERY::INFOS_CARD_CELL_TO_GO:{
                InGameParser game_parser(response);
                std::shared_ptr<MoveByCardInfo> move_card_info = game_parser.parseMoveByCardQuery();
                this->view->getBoard()->movePlayer(move_card_info->new_pos, move_card_info->player);
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL:{
                InGameParser game_parser(response);
                std::shared_ptr<MoveOnCardCellInfo> move_cardcell_info = game_parser.parseMoveOnCardCellQuery();
                this->view->getBoard()->movePlayer(move_cardcell_info->new_pos, move_cardcell_info->player);
                if (this->model->isMyTurn()){
                    this->view->getConsole()->addText("Vous venez de piocher une carte :");
                    this->view->getConsole()->addText(move_cardcell_info->description);
                } else this->view->getConsole()->addText(players_username[move_cardcell_info->player-1] + " pioche un carte.");
                break;
            }

            case QUERY::INFOS_CARD_DESCRIPTION:{
                this->view->getConsole()->addText("Vous venez de piocher une carte :");
                this->view->getConsole()->addText(response);
                break;
            }

            case QUERY::CHOICE_MONEY_CARD:{
                this->view->getConsole()->addText("/pay ou /card");
                break;
            }

            case QUERY::USELESS_MESSAGE:{
                break;
            }

            case QUERY::INFOS_BUILD_PROP:{
                InGameParser game_parser(response);
                std::shared_ptr<std::vector<std::string>> build_mode = game_parser.parseBuildOrSellQuery();
                if (this->model->isMyTurn()){
                    for (auto property : *build_mode.get()){
                        int index = this->view->getBoard()->getCellIndex(property);
                        this->view->getBoard()->setBuildable(index);
                    }
                }
                break;
            }

            case QUERY::INFOS_SELL_BUILD:{
                InGameParser game_parser(response);
                std::shared_ptr<std::vector<std::string>> build_mode = game_parser.parseBuildOrSellQuery();
                if (this->model->isMyTurn()){
                    for (auto property : *build_mode.get()){
                        int index = this->view->getBoard()->getCellIndex(property);
                        this->view->getBoard()->setSalable(index);
                    }
                }
                break;
            }

            case QUERY::INFOS_LEAVE_BUILD_MODE:{
                for (auto property : build_mode){
                    int index = this->view->getBoard()->getCellIndex(property);
                    this->view->getBoard()->leaveSelection(index);
                }
                break;
            }

            case QUERY::INFOS_ASK_FOR_PURCHASE:{
                InGameParser game_parser(response);
                std::shared_ptr<AskForPurchaseInfo> purchase = game_parser.parseAskForPurchaseQuery();

                this->view->getConsole()->addText("Acheter " + purchase->cell_name + " pour " + std::to_string(purchase->amount)+"$ ?");
                this->view->getConsole()->addText("/yes ou /no");
                this->view->getConsole()->addText("Si vous ne l'achetez pas, des encheres debuteront");
                break;
            }

            case QUERY::INFOS_NOT_ENOUGH_MONEY:{
                this->view->getConsole()->addText("Vous ne possedez pas assez d'argent.");
                break;
            }

            default:
                this->view->getConsole()->addText(response);
                break;
        }
    }
}

//todo added from n-curse (init())
void GameCUIController::initGame() {
    // create a thread to receive messages
    std::thread send_thread(&GameCUIController::receiveMsgLoop, this);
    send_thread.detach();
}

void GameCUIController::initScreen(int gamecode) {
    if (! init) return;
    this->view->startWaitingRoom();

    if (this->model->isCreator()){
        this->view->getOwnerWaitingText()->addText("Gamecode : " + std::to_string(gamecode));
        this->view->getPlayersWaitingText()->setHidden();
    } else {
        this->view->getPlayersWaitingText()->addText("Gamecode : " + std::to_string(gamecode));
        this->view->getOwnerWaitingText()->setHidden();
    }
    init = false;
}

//todo added from n-curse
void GameCUIController::startGame(int beginner) {
    this->view->endWaitingRoom();
    this->model->setPlayerTurn(players_username[beginner]);
    if (this->model->getUsername() == players_username[beginner]){
        this->view->startTurn();
        this->model->startTurn();
    }

    this->view->getInfo()->clearAllText();
    for (int i = 1; i<= player_nb; i++) {
        this->view->getBoard()->setPlayer(0, i);
        this->view->getInfo()->addPlayerLine(players_username[i-1]);
        this->view->getInfo()->setPlayerInfo(i, 1500, 0);
    }
}

void GameCUIController::playerJoinUpdate() { this->view->getInfo()->setPlayersInGame(players_username); }


void GameCUIController::update() { this->initGame(); }
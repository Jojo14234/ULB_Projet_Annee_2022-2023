#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>
#include <string>
#include <memory>

#include "GameCUIController.hpp"
#include "../View/GameCUIView.hpp"
#include "../../Model/QueryParser/GameLaunchingParser.hpp"
#include "../../Model/QueryParser/GameStateParser.hpp"


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
                GameLaunchingParser start_parser(response);
                std::shared_ptr<JoinInfo> p_i = start_parser.parseCreateQuery();
                player_nb = p_i->nb_player;
                players_username = p_i->player_usernames;
                this->initScreen(p_i->game_code);
                this->playerJoinUpdate();
                break;
            }

            case QUERY::PLAYER_JOIN_GAME:{
                GameLaunchingParser start_parser(response);
                std::shared_ptr<JoinInfo> p_i = start_parser.parseJoinQuery();
                player_nb = p_i->nb_player;
                players_username = p_i->player_usernames;
                this->initScreen(p_i->game_code);
                this->playerJoinUpdate();
                break;
            }

            case QUERY::INFOS_START: {
                GameLaunchingParser start_parser(response);
                std::shared_ptr<StartInfo> p_i = start_parser.parseStartQuery();
                player_nb = p_i->player_nb;
                players_username = p_i->player_usernames;
                this->startGame(p_i->beginner);
                this->view->getConsole()->addText("La partie commence");
                break;
            }

            case QUERY::INFOS_ROLL_DICE: {
                GameStateParser game_parser(response);
                DiceInformations dice_i = game_parser.parseDiceLine();
                if (this->model->isMyTurn()) {
                    this->view->getDice1()->setText(std::to_string(dice_i.first_value), 0);
                    this->view->getDice2()->setText(std::to_string(dice_i.second_value), 0);
                }  else this->view->getConsole()->addText("Le joueur " + this->model->getPlayerTurn() + " a obtenu un " + std::to_string(dice_i.first_value ) + " et un " + std::to_string(dice_i.second_value));
                break;
            }

            case QUERY::INFOS_GAME: {
                GameStateParser game_parser(response);
                std::vector<PlayerInformations> players = game_parser.parseEndTurnLine(player_nb);
                for (int i = 0; i < player_nb; i++){
                    this->view->getBoard()->movePlayer(players[i].position, i+1);
                    for (unsigned int j = 0; j < players[i].properties.size(); j++){
                        int index = this->view->getBoard()->getCellIndex(players[i].properties[j].name);
                        if (players[i].properties[j].level == 0){
                            this->view->getBoard()->setPurchased(index, i+1);
                        }
                        else this->view->getBoard()->setHouse(index, 2);
                    }

                    this->view->getInfo()->setPlayerInfo(i+1, players[i].money, players[i].jail_card_nb);
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
                GameStateParser game_parser(response);
                PlayerInteractProperty p_i_p = game_parser.parseInteraction();
                int index = this->view->getBoard()->getCellIndex(p_i_p.property_name);
                this->view->getBoard()->movePlayer(index, p_i_p.player);
                break;
            }

            case QUERY::INFOS_PLAYER_BOUGHT: {
                GameStateParser game_parser(response);
                PlayerInteractProperty p_i_p = game_parser.parseInteraction();
                int index = this->view->getBoard()->getCellIndex(p_i_p.property_name);
                this->view->getBoard()->setPurchased(index, p_i_p.player);
                this->view->getInfo()->changePlayerMoney(p_i_p.player, p_i_p.player_money);
                break;
            }

            case QUERY::INFOS_PLAYER_DIDNT_BUY: {
                if(response != this->model->getUsername()) this->view->getConsole()->addText("Le joueur " + response + " n'a pas achete la propriete");
                break;
            }

                // TODO AJOUTER VISUELLE POUR DIRE QUAND UNE PERSONNE A ACHETÉ UNE MAISON/VENDRE + HOTEL

            case QUERY::INFOS_PLAYER_PAID_PLAYER:{
                GameStateParser game_parser(response);
                PlayerPaidPlayerInformations pppi = game_parser.parsePayement();
                if (this->model->isMyTurn()) {
                    this->view->getInfo()->changePlayerMoney(pppi.loser, pppi.loser_money);
                    this->view->getInfo()->changePlayerMoney(pppi.winner, pppi.winner_money);
                    this->view->getConsole()->addText("Vous payez " + std::to_string(pppi.amount) + "$ a " + players_username[pppi.winner-1]);
                } else {
                    this->view->getConsole()->addText(players_username[pppi.loser-1] + " a paye " + std::to_string(pppi.amount) + "$ a " + players_username[pppi.winner-1]);
                }
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL:{
                GameStateParser game_parser(response);
                PlayerInteractMortgagedCell pimc = game_parser.parseMortgagedLine();
                this->view->getConsole()->addText(pimc.username + " est tombe sur une propriete hypotheque");
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL:{
                if (this->model->isMyTurn()) this->view->getConsole()->addText("Vous etes chez vous.");
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL:{
                GameStateParser game_parser(response);
                PlayerInteractTax pit = game_parser.parseTaxLine();
                int index = this->view->getBoard()->getCellIndex(pit.tax_name);
                this->view->getBoard()->movePlayer(index, pit.player);
                this->view->getInfo()->changePlayerMoney(pit.player, pit.player_money);

                if (this->model->isMyTurn()) {
                    this->view->getConsole()->addText("Vous payez " + std::to_string(pit.price) + "$ de taxe");
                } else {
                    this->view->getConsole()->addText(players_username[pit.player-1] + " a paye " + std::to_string(pit.price) + "$ de taxe");
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
                GameStateParser game_parser(response);
                PlayerWonOrLoseMoneyInfo pwolmi = game_parser.parseWonOrLoseMoney();
                this->view->getInfo()->changePlayerMoney(pwolmi.player, pwolmi.player_money);
                if (! this->model->isMyTurn()) this->view->getConsole()->addText(players_username[pwolmi.player-1] + " a gagne " + std::to_string(pwolmi.amount) + "$");
                break;

            }

            case QUERY::INFOS_PLAYER_LOSE_MONEY:{
                GameStateParser game_parser(response);
                PlayerWonOrLoseMoneyInfo pwolmi = game_parser.parseWonOrLoseMoney();
                this->view->getInfo()->changePlayerMoney(pwolmi.player, pwolmi.player_money);
                if (! this->model->isMyTurn()) this->view->getConsole()->addText(players_username[pwolmi.player-1] + " a perdu " + std::to_string(-pwolmi.amount) + "$");
                break;
            }

            case QUERY::INFOS_CARD_CELL_TO_GO:{
                GameStateParser game_parser(response);
                PlayerMoveByCard pmbc = game_parser.parsePlayerMoveByCard();
                this->view->getBoard()->movePlayer(pmbc.new_pos, pmbc.player);
                break;
            }

            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL:{
                GameStateParser game_parser(response);
                PlayerMoveOnCardCell pmocc = game_parser.parseMoveOnCardCell();
                this->view->getBoard()->movePlayer(pmocc.new_pos, pmocc.player);
                if (this->model->isMyTurn()){
                    this->view->getConsole()->addText("Vous venez de piocher une carte :");
                    this->view->getConsole()->addText(pmocc.description);
                } else this->view->getConsole()->addText(players_username[pmocc.player-1] + " a pioche un carte.");
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
                GameStateParser game_parser(response);
                std::vector<std::string> build_mode = game_parser.parsePropertiesName();
                if (this->model->isMyTurn()){
                    for (auto property : build_mode){
                        int index = this->view->getBoard()->getCellIndex(property);
                        this->view->getBoard()->setBuildable(index);
                    }
                }
                break;
            }

            case QUERY::INFOS_SELL_BUILD:{
                GameStateParser game_parser(response);
                std::vector<std::string> build_mode = game_parser.parsePropertiesName();
                if (this->model->isMyTurn()){
                    for (auto property : build_mode){
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
                GameStateParser game_parser(response);
                AskPlayerForPurchase purchase = game_parser.parseAskForPurchase();

                this->view->getConsole()->addText("Acheter " + purchase.cell_name + " pour " + std::to_string(purchase.amount)+"$ ?");
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
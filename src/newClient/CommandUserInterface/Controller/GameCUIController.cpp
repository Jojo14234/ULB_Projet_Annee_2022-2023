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

void GameCUIController::handle(int ch) {
    switch(ch) {
        case KEY_MOUSE:
            MEVENT event;
            if (getmouse(&event) != OK) { break; }
            if (event.bstate & BUTTON1_CLICKED) {
                if ( this->view->getConsole()->isClicked(Position{event.x, event.y}) ) { this->state = CONSOLE; }
                else if ( this->view->getChat()->isClicked(Position{event.x, event.y}) ) { this->state = CHAT; }
                else { this->state = IDLE; }
            }
            break;

        case '\n':
            switch(this->state) {
                case CONSOLE: {
                    this->view->getConsole()->addInput();
                    GameInputParser parser(this->view->getConsole()->getInput());
                    if ( not this->model->sendCommand(parser)) this->view->getConsole()->addText("La commande n'existe pas");
                    break;
                }

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

void GameCUIController::move() {
    switch (this->state) {
        case CHAT: this->view->getChat()->move(); break;
        case CONSOLE: this->view->getConsole()->move(); break;
        case IDLE: break;
    }
}

void GameCUIController::receiveMsgLoop() { // todo il faudrait pas déplacer les fonction appeler par celle-ci dans le view ?
    while (this->new_state == STATE::GAME) {
        std::string response;
        QUERY query = this->model->receive(response);

        switch(query) {
            case QUERY::PLAYER_CREATE_GAME :            this->createGameGU(response); break;
            case QUERY::PLAYER_JOIN_GAME :              this->joinGameGU(response); break;
            case QUERY::INFOS_START :                   this->infoStartGU(response); break;
            case QUERY::INFOS_ROLL_DICE :               this->rollDiceGU(response); break;
            case QUERY::INFOS_GAME :                    this->infoGameGU(response); break;
            case QUERY::INFOS_NEW_TURN :                this->newTurnGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE :             this->playerMoveGU(response); break;
            case QUERY::INFOS_PLAYER_BOUGHT :           this->playerBoughtGU(response); break;
            case QUERY::INFOS_PLAYER_PAID_PLAYER :      this->playerPaidPlayerGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL: this->moveOnMortgagedCellGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL : this->moveOnTaxCellGU(response); break;
            case QUERY::INFOS_PLAYER_GO_OUT_PRISON :    this->goOutPrisonGU(response); break;
            case QUERY::INFOS_PLAYER_SEND_TO_PRISON :   this->sendPrisonGU(response); break;
            case QUERY::GET_GO_OUT_JAIL_CARD :          this->getGoOutJailCardGU(response); break;
            case QUERY::LOST_GO_OUT_JAIL_CARD :         this->loseGoOutJailCardGU(response); break;
            case QUERY::INFOS_PLAYER_WON_MONEY :        this->wonMoneyGU(response); break;
            case QUERY::INFOS_PLAYER_LOSE_MONEY :       this->loseMoneyGU(response); break;
            case QUERY::INFOS_CARD_CELL_TO_GO :         this->cardCellToGoGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL :this->moveOnCardCellGU(response); break;
            case QUERY::INFOS_CARD_DESCRIPTION :        this->drawCardGU(response); break;
            case QUERY::USELESS_MESSAGE :               break;
            case QUERY::INFOS_BUILD_PROP :              this->buildPropertyGU(response); break;
            case QUERY::INFOS_SELL_BUILD :              this->sellPropertyGU(response); break;
            case QUERY::INFOS_LEAVE_BUILD_MODE :        this->leaveBuildMenuGU(response); break;
            case QUERY::INFOS_BUILD_SUCCESS :           this->buildSucceedGU(response); break;
            case QUERY::INFOS_ASK_FOR_PURCHASE :        this->askForPurchaseGU(response); break;

            case QUERY::INFOS_PLAYER_DIDNT_BUY :        if (response != this->model->getUsername()) { this->view->getConsole()->addText("Le joueur " + response + " n'a pas achete la propriete"); } break;
            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL : if (this->model->isMyTurn()) { this->view->getConsole()->addText("Vous etes chez vous."); } break;
            case QUERY::BAD_COMMAND :                   if (this->model->isMyTurn()) { this->view->getConsole()->addText("Vous ne pouvez pas utiliser cette commande"); } break;

            case QUERY::CHOICE_MONEY_CARD :             this->view->getConsole()->addText("/pay ou /card"); break;
            case QUERY::NO_BUILDABLE_PROP :             this->view->getConsole()->addText("Vous n\'avez pas de terrain pouvant avoir de nouveaux batiments"); break;
            case QUERY::CANNOT_BUILD :                  this->view->getConsole()->addText("Ce terrain ne peut pas acceuillir de nouveaux batiments"); break;
            case QUERY::INFOS_NOT_ENOUGH_MONEY :        this->view->getConsole()->addText("Vous ne possedez pas assez d'argent."); break;
            default :                                   this->view->getConsole()->addText(response); break;
        }
    }
}

void GameCUIController::initGame() {
    // create a thread to receive messages
    std::thread send_thread(&GameCUIController::receiveMsgLoop, this);
    send_thread.detach();
}

void GameCUIController::initScreen(int gamecode) {
    if (!init) return;
    this->view->startWaitingRoom();

    if ( this->model->isCreator() ) {
        this->view->getOwnerWaitingText()->addText("Gamecode : " + std::to_string(gamecode));
        this->view->getPlayersWaitingText()->setHidden();
    }
    else {
        this->view->getPlayersWaitingText()->addText("Gamecode : " + std::to_string(gamecode));
        this->view->getOwnerWaitingText()->setHidden();
    }
    init = false;
}

//todo added from n-curse
void GameCUIController::startGame(int beginner) {
    this->view->endWaitingRoom();
    this->model->setPlayerTurn(players_username[beginner]);
    if (this->model->getUsername() == players_username[beginner]) {
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





//Graphical Updates // todo il faut pas déplacer ça dans le view ?

// Les 2 fonctions ci-dessous sont les mêmes WHY ??????
void GameCUIController::createGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<JoinInfo> join_info = launching_parser.parseCreateQuery();
    player_nb = join_info->nb_player;
    players_username = join_info->player_usernames;
    this->initScreen(join_info->game_code);
    this->playerJoinUpdate();
}
void GameCUIController::joinGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<JoinInfo> join_info = launching_parser.parseJoinQuery();
    player_nb = join_info->nb_player;
    players_username = join_info->player_usernames;
    this->initScreen(join_info->game_code);
    this->playerJoinUpdate();
}
// Quasi la même mais y'a La partie commence en plus
void GameCUIController::infoStartGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<StartInfo> start_info = launching_parser.parseStartQuery();
    player_nb = start_info->player_nb;
    players_username = start_info->player_usernames;
    this->startGame(start_info->beginner);
    this->view->getConsole()->addText("La partie commence");
}

void GameCUIController::rollDiceGU(const std::string& response) {
    InGameParser game_parser(response);
    std::shared_ptr<RollDiceInfo> dice_info = game_parser.parseRollDiceQuery();
    if (this->model->isMyTurn()) {
        this->view->getDice1()->setText(std::to_string(dice_info->first_value), 0);
        this->view->getDice2()->setText(std::to_string(dice_info->second_value), 0);
        this->view->getConsole()->addText("Vous avez obtenu un " + std::to_string(dice_info->first_value) + " et un " + std::to_string(dice_info->second_value));
    }  else this->view->getConsole()->addText("Le joueur " + this->model->getPlayerTurn() + " a obtenu un " + std::to_string(dice_info->first_value ) + " et un " + std::to_string(dice_info->second_value));
}

void GameCUIController::infoGameGU(const std::string& response) {
    //Peut-être comportement commun
    InGameParser game_parser(response);
    std::shared_ptr<std::vector<GameInfo>> player_game_info = game_parser.parseInfosGameQuery(player_nb);
    for (int i = 0; i < player_nb; i++){
        this->view->getBoard()->movePlayer(player_game_info->at(i).position, i+1);
        for (unsigned int j = 0; j < player_game_info->at(i).properties.size(); j++){
            int index = this->view->getBoard()->getCellIndex(player_game_info->at(i).properties[j].name);
            if (player_game_info->at(i).properties[j].level == 0){
                this->view->getBoard()->setPurchased(index, i+1);
            }
            else this->view->getBoard()->setHouse(index, player_game_info->at(i).properties[j].level);
        }
        this->view->getInfo()->setPlayerInfo(i+1, player_game_info->at(i).money, player_game_info->at(i).jail_card_nb);
    }
}

void GameCUIController::newTurnGU(const std::string& response) {
    this->model->setPlayerTurn(response);
    if (response == this->model->getUsername()) { this->view->startTurn(); this->model->startTurn(); }
    else { this->view->endTurn(); this->model->endTurn(); this->view->getConsole()->addText("C'est au tour de " + response + " !"); }
}

void GameCUIController::playerMoveGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->getBoard()->getCellIndex(move_info->property_name);
    this->view->getBoard()->movePlayer(index, move_info->player);
    if (move_info->property_name == "Prison" and this->model->isMyTurn()){
        this->view->getConsole()->addText("Vous visitez la prison.");
    } else if (move_info->property_name == "Start" and this->model->isMyTurn()){
        this->view->getConsole()->addText("Vous arrivez sur la case départ.");
    } else if (move_info->property_name == "Parc" and this->model->isMyTurn()){
        this->view->getConsole()->addText("Vous arrivez au parc gratuit.");
    }
}

void GameCUIController::playerBoughtGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->getBoard()->getCellIndex(move_info->property_name);
    this->view->getBoard()->setPurchased(index, move_info->player);
    this->view->getInfo()->changePlayerMoney(move_info->player, move_info->player_money);
}

void GameCUIController::playerPaidPlayerGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerPaidPlayerInfo> payement_info = game_parser.parsePlayerPaidPlayerQuery();
    if (this->model->isMyTurn()) {
        this->view->getInfo()->changePlayerMoney(payement_info->loser, payement_info->loser_money);
        this->view->getInfo()->changePlayerMoney(payement_info->winner, payement_info->winner_money);
        this->view->getConsole()->addText("Vous devez " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
    } else {
        this->view->getConsole()->addText(players_username[payement_info->loser-1] + " doit " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
    }
}

void GameCUIController::moveOnMortgagedCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveMortgagedInfo> mortgaged_info = game_parser.parseMoveMortgagedQuery();
    this->view->getConsole()->addText(mortgaged_info->username + " est tombe sur une propriete hypotheque");
}

void GameCUIController::moveOnTaxCellGU(const std::string& response){
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
}

void GameCUIController::goOutPrisonGU(const std::string& response){
    if (this->model->isMyTurn()){ this->view->getConsole()->addText("Vous sortez de prison.");
    } else this->view->getConsole()->addText(response + "sort de prison.");
}

void GameCUIController::sendPrisonGU(const std::string& response){
    if (this->model->isMyTurn()){this->view->getConsole()->addText("Vous etes envoye en prison.");
    } else this->view->getConsole()->addText(response + " a ete envoye en prison.");
}

void GameCUIController::getGoOutJailCardGU(const std::string& response){
    this->view->getInfo()->addCardToPlayer(atoi(response.c_str()));
    if (this->model->isMyTurn()){ this->view->getConsole()->addText("Vous obtenez une carte sortie de prison.");
    } else this->view->getConsole()->addText(players_username[atoi(response.c_str()-1)] + "a obtenu une carte sortie de prison.");
}

void GameCUIController::loseGoOutJailCardGU(const std::string& response){
    this->view->getInfo()->removeCardToPlayer(atoi(response.c_str()));
    if (this->model->isMyTurn()) this->view->getConsole()->addText("Vous utilisez votre carte.");
}

void GameCUIController::wonMoneyGU(const std::string& response){
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
}

void GameCUIController::loseMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->getInfo()->changePlayerMoney(money_info->player, money_info->player_money);
    if (! this->model->isMyTurn()) this->view->getConsole()->addText(players_username[money_info->player-1] + " a perdu " + std::to_string(money_info->amount) + "$");
    else { 
        if (players_username[money_info->player-1] == this->model->getUsername()){
            this->view->getConsole()->addText("Vous perdez " + std::to_string(money_info->amount) + "$"); 
        }
        else this->view->getConsole()->addText(players_username[money_info->player-1] + " perd " + std::to_string(money_info->amount) + "$");
    }
}

void GameCUIController::cardCellToGoGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveByCardInfo> move_card_info = game_parser.parseMoveByCardQuery();
    this->view->getBoard()->movePlayer(move_card_info->new_pos, move_card_info->player);
}

void GameCUIController::moveOnCardCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveOnCardCellInfo> move_cardcell_info = game_parser.parseMoveOnCardCellQuery();
    this->view->getBoard()->movePlayer(move_cardcell_info->new_pos, move_cardcell_info->player);
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("Vous venez de piocher une carte :");
        this->view->getConsole()->addText(move_cardcell_info->description);
    } else this->view->getConsole()->addText(players_username[move_cardcell_info->player-1] + " pioche un carte.");
}

void GameCUIController::drawCardGU(const std::string& response){
    this->view->getConsole()->addText("Vous venez de piocher une carte :");
    this->view->getConsole()->addText(response);
}

void GameCUIController::buildPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    build_mode = *game_parser.parseBuildOrSellQuery().get();
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("/select [nom] pour construire un batiment");
        this->view->getConsole()->addText("/leave pour quitter le menu de construction");
        for (auto& property : build_mode){
            int index = this->view->getBoard()->getCellIndex(property);
            this->view->getBoard()->setBuildable(index);
        }
    } else this->view->getConsole()->addText("Consultation du menu de construction...");
}

void GameCUIController::sellPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    build_mode = *game_parser.parseBuildOrSellQuery().get();
    if (this->model->isMyTurn()){
        for (auto& property : build_mode){
            int index = this->view->getBoard()->getCellIndex(property);
            this->view->getBoard()->setSalable(index);
        }
    }
}

void GameCUIController::leaveBuildMenuGU(const std::string& response){
    for (auto& property : build_mode) {
        int index = this->view->getBoard()->getCellIndex(property);
        this->view->getBoard()->leaveSelection(index);
    }
}

void GameCUIController::buildSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildSuccessInfo> success_info = game_parser.parseBuildSuccessQuery();
    int index = this->view->getBoard()->getCellIndex(success_info->name);
    this->view->getBoard()->setHouse(index, success_info->level);
}

void GameCUIController::askForPurchaseGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<AskForPurchaseInfo> purchase = game_parser.parseAskForPurchaseQuery();
    this->view->getConsole()->addText("Acheter " + purchase->cell_name + " pour " + std::to_string(purchase->amount)+"$ ?");
    this->view->getConsole()->addText("/yes ou /no");
    this->view->getConsole()->addText("Si vous ne l'achetez pas, des encheres debuteront");
}

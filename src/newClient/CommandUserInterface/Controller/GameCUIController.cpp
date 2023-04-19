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

//MAX 64 CHAR / LIGNES

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
            case QUERY::INFOS_NOT_STARTED :             this->view->getConsole()->addText("Pour démarrer la partie ( /start )"); break;
            case QUERY::INFOS_CANNOT_START :            this->view->getConsole()->addText("Attend tes amis avant de lancer la partie !"); break;
            case QUERY::INFOS_ROLL_DICE :               this->rollDiceGU(response); break;
            case QUERY::INFOS_GAME :                    this->infoGameGU(response); break;
            case QUERY::INFOS_NEW_TURN :                this->newTurnGU(response); break;
            case QUERY::INFOS_NEW_TURN_IN_JAIL:         this->newTurnInJailGU(response); break;
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
            case QUERY::INFOS_MORTGAGEABLE_PROP :       this->mortgagePropertyGU(response); break;
            case QUERY::INFOS_LIFT_MORTGAGEABLE_PROP :  this->unmortgagePropertyGU(response); break;
            case QUERY::INFOS_EXCHANGEABLE_PROP :       this->exchangePropertyGU(response); break;            
            case QUERY::INFOS_LEAVE_SELECTION_MODE :    this->leaveSelectionMenuGU(); break;

            case QUERY::INFOS_BUILD_SUCCESS :
            case QUERY::INFOS_SELL_BUILD_SUCCESS :      this->buildOrSellSucceedGU(response); break;
            case QUERY::INFOS_MORTGAGE_SUCCESS :        this->mortgageSucceedGU(response); break;
            case QUERY::INFOS_LIFT_MORTGAGE_SUCCESS :   this->unmortgageSucceedGU(response); break;
			case QUERY::INFOS_EXCHANGE_SUCCESS : 		this->exchangeSucceedGU(response); break;

            case QUERY::INFOS_ASK_FOR_PURCHASE :        this->askForPurchaseGU(response); break;
            case QUERY::ASK_EXCHANGE :                  this->askExchangeGU(response); break;
            case QUERY::CONFIRM_EXCHANGE_ASKING :       this->confirmExchangeAskingGU(response); break;

            case QUERY::INFOS_AUCTION_START :           this->startAuctionGU(response); break;
            case QUERY::INFOS_AUCTION_BID :             this->auctionBidGU(response); break;
            case QUERY::INFOS_AUCTION_END :             this->endAuctionGU(response); break;
            case QUERY::WAIT_YOUR_TURN :                this->view->getConsole()->addText("Votre tour d'enchère a prit fin, attendez le suivant."); break;
            case QUERY::BAD_AMOUNT :                    this->view->getConsole()->addText("Le montant entre n'est pas correct"); break;
            case QUERY::NOT_ENOUGH_MONEY_TO_PARTICIPATE:this->view->getConsole()->addText("Vous n'avez plus assez d'argent pour continuer a participer."); break;
            case QUERY::LEAVE_BID:                      this->view->getConsole()->addText("Vous avez abandonne les encheres"); break;

            case QUERY::INFOS_PLAYER_DIDNT_BUY :        if (response != this->model->getUsername()) { this->view->getConsole()->addText("Le joueur " + response + " n'a pas achete la propriete"); } break;
            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL : if (this->model->isMyTurn()) { this->view->getConsole()->addText("Vous etes chez vous."); } break;
            case QUERY::BAD_COMMAND :                   if (this->model->isMyTurn()) { this->view->getConsole()->addText("Vous ne pouvez pas utiliser cette commande"); } break;

            case QUERY::CHOICE_MONEY_CARD :             this->view->getConsole()->addText("/pay ou /card"); break;
            case QUERY::NO_BUILDABLE_PROP :             this->view->getConsole()->addText("Vous n\'avez pas de terrain pouvant avoir de nouveaux batiments"); break;
            case QUERY::NO_SALABLE_PROP :               this->view->getConsole()->addText("Vous n\'avez pas de terrain pouvant etre vendu"); break;
            case QUERY::NO_MORTGAGEABLE_PROP :          this->view->getConsole()->addText("Vous n\'avez pas de terrain pouvant etre hypoteque"); break;
            case QUERY::NO_UNMORTGAGEABLE_PROP :        this->view->getConsole()->addText("Vous n\'avez pas de terrain pouvant etre deshypotheque"); break;
            case QUERY::NO_EXCHANGEABLE_PROP :			this->view->getConsole()->addText("Il n'y a pas de terrain disponible a l'echange"); break;

            case QUERY::CANNOT_BUILD :                  this->view->getConsole()->addText("Ce terrain ne peut pas acceuillir de nouveaux batiments"); break;
            case QUERY::CANNOT_SELL :                   this->view->getConsole()->addText("Ce terrain ne peut pas perdre des batiments"); break;
            case QUERY::CANNOT_MORTAGE :                this->view->getConsole()->addText("Ce terrain ne peut pas etre hypotheque"); break;
            case QUERY::CANNOT_UNMORTGAGE :             this->view->getConsole()->addText("Ce terrain ne peut pas etre deshypotheque"); break;
            case QUERY::CANNOT_EXCHANGE :				this->view->getConsole()->addText("Ce terrain ne peut pas etre echange"); break;

            case QUERY::EXCHANGE_REFUSED :              this->view->getConsole()->addText("L'echange a ete refuse"); break;
            case QUERY::INFOS_NOT_ENOUGH_MONEY :        this->view->getConsole()->addText("Vous ne possedez pas assez d'argent."); break;
            case QUERY::INFOS_AUTO_OTHER_POSSIBILITY:   this->view->getConsole()->addText("L'autre possibilite a ete automatiquement selectionnee"); break;
            case QUERY::STOP_WAIT :                     this->view->getConsole()->addText("Pas assez rapide. L'offre a ete automatiquement annulee"); this->model->sendCommand(GameInputParser{response}); break;
            
            case QUERY::INFOS_DEBT :                    break;
            case QUERY::INFOS_WON_LAND :                this->wonLandGU(response); break;

            case QUERY::WIN :                           this->endGameGU(response); break;
            case QUERY::ENDGAME :                       break;
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
    this->model->setPlayerTurn(game_info->player_usernames[beginner]);
    if (this->model->getUsername() == game_info->player_usernames[beginner]) {
        this->view->startTurn();
        this->model->startTurn();
    }

    this->view->getInfo()->clearAllText();
    for (int i = 1; i<= game_info->nb_player; i++) {
        this->view->getBoard()->setPlayer(0, i);
        this->view->getInfo()->addPlayerLine(game_info->player_usernames[i-1]);
        this->view->getInfo()->setPlayerInfo(i, game_info->start_money, 0);
    }
}

void GameCUIController::playerJoinUpdate() { this->view->getInfo()->setPlayersInGame(game_info->player_usernames); }


void GameCUIController::update() { this->initGame(); }





//Graphical Updates // todo il faut pas déplacer ça dans le view ?

// Les 2 fonctions ci-dessous sont les mêmes WHY ??????
void GameCUIController::createGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    game_info = launching_parser.parseCreateQuery();
    this->initScreen(game_info->game_code);
    this->playerJoinUpdate();
}
void GameCUIController::joinGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    game_info = launching_parser.parseJoinQuery();
    this->initScreen(game_info->game_code);
    this->playerJoinUpdate();
}
// Quasi la même mais y'a La partie commence en plus
void GameCUIController::infoStartGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<StartInfo> start_info = launching_parser.parseStartQuery();
    game_info->nb_player = start_info->player_nb;
    game_info->player_usernames = start_info->player_usernames;
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
    std::shared_ptr<std::vector<GameInfo>> player_game_info = game_parser.parseInfosGameQuery(game_info->nb_player);
    for (int i = 0; i < game_info->nb_player; i++){
        this->view->getBoard()->movePlayer(player_game_info->at(i).position, i+1);
        for (unsigned int j = 0; j < player_game_info->at(i).properties.size(); j++){
            int index = this->view->getBoard()->getCellIndex(player_game_info->at(i).properties[j].name);
            if (player_game_info->at(i).properties[j].mortgage){
                this->view->getBoard()->setMortgaged(index);
            }
            else if (player_game_info->at(i).properties[j].level == 0){
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

void GameCUIController::newTurnInJailGU(const std::string& response) {
    JailInfo jail_info(response);
    this->view->getConsole()->addText("Vous êtes en prison depuis " + std::to_string(jail_info.nb_turn) + " tours !");
    std::string str = jail_info.has_card ? "/roll (tenter un double), /pay (50$) ou /card (utiliser carte)" : "/roll (tenter un double) ou /pay (50$)";
    this->view->getConsole()->addText(str);
}

void GameCUIController::playerMoveGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->getBoard()->getCellIndex(move_info->property_name);
    this->view->getBoard()->movePlayer(index, move_info->player);
    if (move_info->property_name == "Prison" and this->model->isMyTurn()){
        this->view->getConsole()->addText("Vous arrivez sur la case prison.");
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
        this->view->getConsole()->addText("Vous devez " + std::to_string(payement_info->amount) + "$ a " + game_info->player_usernames[payement_info->winner-1] + " :");
    } else {
        this->view->getConsole()->addText(game_info->player_usernames[payement_info->loser-1] + " doit " + std::to_string(payement_info->amount) + "$ a " + game_info->player_usernames[payement_info->winner-1] + " :");
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
        this->view->getConsole()->addText(game_info->player_usernames[tax_info->player-1] + " paie ses taxes : ");
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
    } else this->view->getConsole()->addText(game_info->player_usernames[atoi(response.c_str()-1)] + "a obtenu une carte sortie de prison.");
}

void GameCUIController::loseGoOutJailCardGU(const std::string& response){
    this->view->getInfo()->removeCardToPlayer(atoi(response.c_str()));
    if (this->model->isMyTurn()) this->view->getConsole()->addText("Vous utilisez votre carte.");
}

void GameCUIController::wonMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->getInfo()->changePlayerMoney(money_info->player, money_info->player_money);
    if (! this->model->isMyTurn()) { this->view->getConsole()->addText(game_info->player_usernames[money_info->player-1] + " a gagne " + std::to_string(money_info->amount) + "$"); }
    else { 
        if (game_info->player_usernames[money_info->player-1] == this->model->getUsername()){
            this->view->getConsole()->addText("Vous gagnez " + std::to_string(money_info->amount) + "$");
        }
        else this->view->getConsole()->addText(game_info->player_usernames[money_info->player-1] + " gagne " + std::to_string(money_info->amount) + "$");
    }
}

void GameCUIController::loseMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->getInfo()->changePlayerMoney(money_info->player, money_info->player_money);
    if (! this->model->isMyTurn()) this->view->getConsole()->addText(game_info->player_usernames[money_info->player-1] + " a perdu " + std::to_string(money_info->amount) + "$");
    else { 
        if (game_info->player_usernames[money_info->player-1] == this->model->getUsername()){
            this->view->getConsole()->addText("Vous perdez " + std::to_string(money_info->amount) + "$"); 
        }
        else this->view->getConsole()->addText(game_info->player_usernames[money_info->player-1] + " perd " + std::to_string(money_info->amount) + "$");
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
    } else this->view->getConsole()->addText(game_info->player_usernames[move_cardcell_info->player-1] + " pioche un carte.");
}

void GameCUIController::drawCardGU(const std::string& response){
    this->view->getConsole()->addText("Vous venez de piocher une carte :");
    this->view->getConsole()->addText(response);
}

void GameCUIController::buildPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("/select [nom] pour construire un batiment");
        this->view->getConsole()->addText("/leave pour quitter le menu de construction");
        for (auto& property : selection_mode){
            int index = this->view->getBoard()->getCellIndex(property);
            this->view->getBoard()->setBuildable(index);
        }
    } else this->view->getConsole()->addText("Consultation des batiments a construire...");
}

void GameCUIController::sellPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("/select [nom] pour vendre un batiment");
        this->view->getConsole()->addText("/leave pour quitter le menu de vente");
        for (auto& property : selection_mode){
            int index = this->view->getBoard()->getCellIndex(property);
            this->view->getBoard()->setSalable(index);
        }
    } else this->view->getConsole()->addText("Consultation des proprietes a vendre ...");
}
void GameCUIController::exchangePropertyGU(const std::string& response){
    ExchangeInfo exchanges{response, game_info->nb_player};
    selection_mode = exchanges.all_properties;
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("/trade [nom_propiete_voulue] [argent]");
        this->view->getConsole()->addText("/leave pour quitter le menu d'echange");
        for (int i=0; i<game_info->nb_player; i++){
            for (auto& property : exchanges.player_properties.at(i)){
                int index = this->view->getBoard()->getCellIndex(property);
                this->view->getBoard()->setExchangeable(index);
            }
        }
    } else this->view->getConsole()->addText("Consultation des echanges ...");

}

void GameCUIController::mortgagePropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("/select [nom] pour hypotequer un batiment");
        this->view->getConsole()->addText("/leave pour quitter le menu de selection");
        for (auto& property : selection_mode){
            int index = this->view->getBoard()->getCellIndex(property);
            this->view->getBoard()->setMortgageable(index);
        }
    } else this->view->getConsole()->addText("Consultation des proprietes a hypotequer ...");
}

void GameCUIController::unmortgagePropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->getConsole()->addText("/select [nom] pour deshypotequer un batiment");
        this->view->getConsole()->addText("/leave pour quitter le menu de selection");
        for (auto& property : selection_mode){
            int index = this->view->getBoard()->getCellIndex(property);
            this->view->getBoard()->setUnmortgageable(index);
        }
    } else this->view->getConsole()->addText("Consultation des proprietes a deshypotequer ...");
}

void GameCUIController::leaveSelectionMenuGU(){
    for (auto& property : selection_mode) {
        int index = this->view->getBoard()->getCellIndex(property);
        this->view->getBoard()->leaveSelection(index);
    }
}

void GameCUIController::buildOrSellSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    int index = this->view->getBoard()->getCellIndex(success_info->name);
    this->view->getBoard()->setHouse(index, success_info->level);
}

void GameCUIController::mortgageSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    int index = this->view->getBoard()->getCellIndex(success_info->name);
    this->view->getBoard()->setMortgaged(index);
}

void GameCUIController::unmortgageSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    int index = this->view->getBoard()->getCellIndex(success_info->name);
    this->view->getBoard()->unmortgage(index);
}

void GameCUIController::exchangeSucceedGU(const std::string & response){
	ExchangeSucceedInfo succeed(response);
	int index = this->view->getBoard()->getCellIndex(succeed.property);
    if (this->model->isMyTurn()) this->view->getBoard()->leaveSelection(index);
	this->view->getBoard()->setPurchased(index, succeed.player);
}

void GameCUIController::askExchangeGU(const std::string & response){
    AskExchangeInfo exchange_info(response);
    this->view->getConsole()->addText(exchange_info.username + " aimerait vous racheter " + exchange_info.property + " pour " + std::to_string(exchange_info.price) +"$");
    this->view->getConsole()->addText("/accept ou /refuse");
}

void GameCUIController::confirmExchangeAskingGU(const std::string& response){
    AskExchangeInfo exchange_info(response);
    this->view->getConsole()->addText("La demande de rachat de " + exchange_info.property + " pour " + std::to_string(exchange_info.price) + "$ a ete envoyee a " + exchange_info.username);
}

void GameCUIController::askForPurchaseGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<AskForPurchaseInfo> purchase = game_parser.parseAskForPurchaseQuery();
    this->view->getConsole()->addText("Acheter " + purchase->cell_name + " pour " + std::to_string(purchase->amount)+"$ ?");
    this->view->getConsole()->addText("/yes ou /no");
    this->view->getConsole()->addText("Si vous ne l'achetez pas, des encheres debuteront");
}

void GameCUIController::startAuctionGU(const std::string& response){
    BetInfo bet(response);
    this->view->getConsole()->addText("Des encheres pour acheter " + bet.property + " debutent !");
}

void GameCUIController::auctionBidGU(const std::string& response){
    PlayerBetInfo bet(response);
    if (bet.player != ""){
        this->view->getConsole()->addText(bet.player + " est sur le point d'acheter le terrain pour : " + std::to_string(bet.amount) + "$");
    }
    else this->view->getConsole()->addText("Le prix d'achat est actuellement de : " + std::to_string(bet.amount) + "$ !");
    if (! this->model->isMyTurn() && bet.player == "") this->view->getConsole()->addText("/bid pour surencherir, /out pour vous arreter");
}

void GameCUIController::endAuctionGU(const std::string& response){
    EndAuctionInfo end(response);
    if (end.player != ""){
        this->view->getConsole()->addText(end.player + " remporte " + end.property + " pour " + std::to_string(end.amount) + "$ !");
    }
    else this->view->getConsole()->addText("Personne ne remporte " + end.property + ".");
}

void GameCUIController::endGameGU(const std::string& response){
    this->view->getConsole()->addText("Victoire de " + response + ". Félicitations !");
    this->view->getConsole()->addText("Entrez /quit pour retourner au menu.");
    this->view->endTurn();
}

void GameCUIController::wonLandGU(const std::string& response){
    WonLand won_land(response);
    int index = this->view->getBoard()->getCellIndex(won_land.land);
    this->view->getBoard()->setPurchased(index, won_land.player);
}
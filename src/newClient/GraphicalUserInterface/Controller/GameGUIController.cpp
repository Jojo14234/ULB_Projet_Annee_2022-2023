#include <SFML/Window.hpp>

#include "GameGUIController.hpp"
#include "../View/GameGUIView.hpp"
#include "../../Model/Client.hpp"


void GameGUIController::handle(sf::Event event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
            if(this->view->button_mode == "start_round"){
                if(this->view->mortgage_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->unmortgage_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->sell_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->construct_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->roll_dice_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "empty_cell"){
                if(this->view->buy_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->no_buy_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "paid_cell"){
                if(this->view->paid_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "card_cell"){
                if(this->view->draw_card_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "on_prison"){
                if(this->view->paid_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->roll_dice_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->card_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "exchange_round"){
                if(this->view->yes_exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->no_exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "bankrupt_round"){
                if(this->view->sell_bankrupt_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->give_up_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "auction_round"){
                if(this->view->auction_box.getUpButton()->contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->auction_box.getDownButton()->contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->auction_box.getValidateButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                    //TODo
                    this->view->setAuctionRound(false);
                        }}}
/*
void GameGUIController::receiveMsgLoop() { // todo il faudrait pas déplacer les fonction appeler par celle-ci dans le view ?
    while (this->new_state == STATE::GAME){
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
            case QUERY::INFOS_MORTGAGEABLE_PROP :       this->mortgagePropertyGU(response); break;
            case QUERY::INFOS_LIFT_MORTGAGEABLE_PROP :  this->unmortgagePropertyGU(response); break;
            case QUERY::INFOS_EXCHANGEABLE_PROP :       this->exchangePropertyGU(response); break;            
            case QUERY::INFOS_LEAVE_SELECTION_MODE :    this->leaveSelectionMenuGU(response); break;

            case QUERY::INFOS_BUILD_SUCCESS :
            case QUERY::INFOS_SELL_BUILD_SUCCESS :      this->buildOrSellSucceedGU(response); break;
            case QUERY::INFOS_MORTGAGE_SUCCESS :        this->mortgageSucceedGU(response); break;
            case QUERY::INFOS_LIFT_MORTGAGE_SUCCESS :   this->unmortgageSucceedGU(response); break;
			case QUERY::INFOS_EXCHANGE_SUCCESS : 		this->exchangeSucceedGU(response); break;

            case QUERY::INFOS_ASK_FOR_PURCHASE :        this->askForPurchaseGU(response); break;
            case QUERY::ASK_EXCHANGE :                  this->askExchangeGU(response); break;
            case QUERY::CONFIRM_EXCHANGE_ASKING :       this->confirmExchangeAskingGU(response); break;

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
            default :                                   this->view->getConsole()->addText(response); break;
        }
    }
}


void GameGUIController::initScreen(int gamecode) {
    if (!init) return;
    //this->view->startWaitingRoom(); à rajouter dans le plateau
    if ( this->model->isCreator() ) {
        //this->view->getOwnerWaitingText()->addText("Gamecode : " + std::to_string(gamecode)); à rajouter au milieu du plateau
        this->view->message_box.setString("Vous êtes le propriétaire de cette partie, utilisez /start pour lancer la partie");
    }
    else {
        //this->view->getPlayersWaitingText()->addText("Gamecode : " + std::to_string(gamecode));  à rajouter au milieu du plateau
        this->view->message_box.setString("En attente du lancement de la partie...");
    }
    init = false;
}


void GameGUIController::startGame(int beginner) {
    //this->view->endWaitingRoom(); à rajouter dans le plateau
    this->model->setPlayerTurn(players_username[beginner]);
    if (this->model->getUsername() == players_username[beginner]) {
        this->view->startTurn();
        this->model->startTurn();
        //rajouter sons - début game
    }

    //this->view->getInfo()->clearAllText();
    this->view->board.setColorNumber(player_nb);
    this->view->info_box.initMoney(player_nb,1500); //à rajouter carte prison
    for (int i = 1; i<= player_nb; i++) {
        this->view->board.setPlayer(0, i);
        //this->view->InfoBox.initMoney(players_username[i-1]); à rajouter pseudoc 
       
    }
}

//////////////////////////////////////////////////////// 


void GameGUIController::createGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<JoinInfo> join_info = launching_parser.parseCreateQuery();
    player_nb = join_info->nb_player;
    players_username = join_info->player_usernames;
    this->initScreen(join_info->game_code);
    this->playerJoinUpdate();
}


void GameGUIController::joinGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<JoinInfo> join_info = launching_parser.parseJoinQuery();
    player_nb = join_info->nb_player;
    players_username = join_info->player_usernames;
    this->initScreen(join_info->game_code);
    this->playerJoinUpdate();
}


void GameGUIController::infoStartGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<StartInfo> start_info = launching_parser.parseStartQuery();
    player_nb = start_info->player_nb;
    players_username = start_info->player_usernames;
    this->view->message_box.setString("La partie commence");
    this->startGame(start_info->beginner);
}

void GameGUIController::rollDiceGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<RollDiceInfo> dice_info = game_parser.parseRollDiceQuery();
    if (this->model->isMyTurn()){
        // à rajouter 
        //this->view->getDice1()->setText(std::to_string(dice_info->first_value), 0);
        //this->view->getDice2()->setText(std::to_string(dice_info->second_value), 0);

        this->view->message_box.setString("Vous avez obtenu un " + std::to_string(dice_info->first_value) + " et un " + std::to_string(dice_info->second_value));}  
    else this->view->message_box.setString("Le joueur " + this->model->getPlayerTurn() + " a obtenu un " + std::to_string(dice_info->first_value ) + " et un " + std::to_string(dice_info->second_value));
}


void GameGUIController::infoGameGU(const std::string& response) {
    InGameParser game_parser(response);
    std::shared_ptr<std::vector<GameInfo>> player_game_info = game_parser.parseInfosGameQuery(player_nb);
    for (int i = 0; i < player_nb; i++){
        this->view->board.movePlayer(player_game_info->at(i).position, i);
        for (unsigned int j = 0; j < player_game_info->at(i).properties.size(); j++){
            int index = this->view->board.getCellIndex(player_game_info->at(i).properties[j].name);
            if (player_game_info->at(i).properties[j].level == 0){
                this->view->board.setPurchased(index, i);
            }
            else this->view->board.setHouse(index, player_game_info->at(i).properties[j].level);
        }
        this->view->info_box.setMoney(i, player_game_info->at(i).money
        //, player_game_info->at(i).jail_card_nb
        );
        //à rajouter jail card
    }}


void GameGUIController::newTurnGU(const std::string& response) {
    this->model->setPlayerTurn(response);
    if (response == this->model->getUsername()) { this->view->startTurn(); this->model->startTurn();}
    else { 
        this->view->endTurn(); 
        this->model->endTurn(); 
        this->view->message_box.setString("C'est au tour de " + response + " !"); }}



void GameGUIController::playerMoveGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->board.getCellIndex(move_info->property_name);
    this->view->board.movePlayer(index, move_info->player - 1);
    if (move_info->property_name == "Prison" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous visitez la prison.");
    } else if (move_info->property_name == "Start" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez sur la case départ.");
    } else if (move_info->property_name == "Parc" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez au parc gratuit.");
    }
}

void GameGUIController::playerBoughtGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->board.getCellIndex(move_info->property_name);
    this->view->board.setPurchased(index, move_info->player);
    this->view->info_box.setMoney(move_info->player, move_info->player_money);
}


void GameGUIController::playerPaidPlayerGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerPaidPlayerInfo> payement_info = game_parser.parsePlayerPaidPlayerQuery();
    if (this->model->isMyTurn()) {
        this->view->info_box.setMoney(payement_info->loser, payement_info->loser_money);
        this->view->info_box.setMoney(payement_info->winner, payement_info->winner_money);
        this->view->message_box.setString("Vous devez " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
    } else {
        this->view->message_box.setString(players_username[payement_info->loser-1] + " doit " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
    }
}

void GameGUIController::moveOnMortgagedCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveMortgagedInfo> mortgaged_info = game_parser.parseMoveMortgagedQuery();
    this->view->message_box.setString(mortgaged_info->username + " est tombe sur une propriete hypotheque");
}

void GameGUIController::moveOnTaxCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveTaxInfo> tax_info = game_parser.parseMoveTaxQuery();
    int index = this->view->board.getCellIndex(tax_info->tax_name);
    this->view->board.movePlayer(index, tax_info->player);
    this->view->info_box.setMoney(tax_info->player, tax_info->player_money);

    if (this->model->isMyTurn()) {
        this->view->message_box.setString("Vous arrivez sur la case " + tax_info->tax_name + " :");
    } else {
        this->view->message_box.setString(players_username[tax_info->player-1] + " paie ses taxes : ");
    }
}

void GameGUIController::goOutPrisonGU(const std::string& response){
    if (this->model->isMyTurn()){ this->view->message_box.setString("Vous sortez de prison.");
    } else this->view->message_box.setString(response + "sort de prison.");
}

void GameGUIController::sendPrisonGU(const std::string& response){
    if (this->model->isMyTurn()){this->view->message_box.setString("Vous etes envoye en prison.");
    } else this->view->message_box.setString(response + " a ete envoye en prison.");
}

void GameGUIController::getGoOutJailCardGU(const std::string& response){
    //this->view->getInfo()->addCardToPlayer(atoi(response.c_str())); à rajouter
    if (this->model->isMyTurn()){ this->view->message_box.setString("Vous obtenez une carte sortie de prison.");
    } else this->view->message_box.setString(players_username[atoi(response.c_str()-1)] + "a obtenu une carte sortie de prison.");
}


void GameGUIController::loseGoOutJailCardGU(const std::string& response){
    //this->view->getInfo()->removeCardToPlayer(atoi(response.c_str())); à rajouter 
    if (this->model->isMyTurn()) this->view->message_box.setString("Vous utilisez votre carte.");
}

void GameGUIController::wonMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->info_box.setMoney(money_info->player, money_info->player_money);
    if (! this->model->isMyTurn()) { this->view->message_box.setString(players_username[money_info->player-1] + " a gagne " + std::to_string(money_info->amount) + "$"); }
    else { 
        if (players_username[money_info->player-1] == this->model->getUsername()){
            this->view->message_box.setString("Vous gagnez " + std::to_string(money_info->amount) + "$");
        }
        else this->view->message_box.setString(players_username[money_info->player-1] + " gagne " + std::to_string(money_info->amount) + "$");
    }
}

void GameGUIController::loseMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->info_box.setMoney(money_info->player, money_info->player_money);
    if (! this->model->isMyTurn()) this->view->message_box.setString(players_username[money_info->player-1] + " a perdu " + std::to_string(money_info->amount) + "$");
    else { 
        if (players_username[money_info->player-1] == this->model->getUsername()){
            this->view->message_box.setString("Vous perdez " + std::to_string(money_info->amount) + "$"); 
        }
        else this->view->message_box.setString(players_username[money_info->player-1] + " perd " + std::to_string(money_info->amount) + "$");
    }
}

void GameGUIController::cardCellToGoGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveByCardInfo> move_card_info = game_parser.parseMoveByCardQuery();
    this->view->board.movePlayer(move_card_info->new_pos, move_card_info->player-1);
}

void GameGUIController::moveOnCardCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveOnCardCellInfo> move_cardcell_info = game_parser.parseMoveOnCardCellQuery();
    this->view->board.movePlayer(move_cardcell_info->new_pos, move_cardcell_info->player);
    if (this->model->isMyTurn()){
        this->view->message_box.setString("Vous venez de piocher une carte :");
        //this->view->getConsole()->addText(move_cardcell_info->description); à rajouter zone au milieu pour description
    } else this->view->message_box.setString(players_username[move_cardcell_info->player-1] + " pioche un carte.");
}*/
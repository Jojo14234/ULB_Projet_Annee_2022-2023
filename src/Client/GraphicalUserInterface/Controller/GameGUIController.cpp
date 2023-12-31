#include <SFML/Window.hpp>

#include "GameGUIController.hpp"
#include "../View/GameGUIView.hpp"
#include "../../Model/Client.hpp"



void GameGUIController::handle(sf::Event event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
            if(this->view->button_mode == "start_game"){
                if(this->view->startgame_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->startgame_button.playSound();
                    GameInputParser parser("/start");
                    this->model->sendCommand(parser);
                    this->view->setStartGame(false);
                        }}
            else if(this->view->button_mode == "start_round"){
                if(this->view->mortgage_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->mortgage_button.playSound();
                    GameInputParser parser("/mortgage");
                    this->model->sendCommand(parser);
                    this->view->setStartRound(false);
                        }
                else if(this->view->unmortgage_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->unmortgage_button.playSound();
                    GameInputParser parser("/unmortgage");
                    this->model->sendCommand(parser);
                    this->view->setStartRound(false);
                        }
                else if(this->view->sell_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->sell_button.playSound();
                    GameInputParser parser("/sell");
                    this->model->sendCommand(parser);
                    this->view->setStartRound(false);
                        }
                else if(this->view->construct_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->construct_button.playSound();
                    GameInputParser parser("/build");
                    this->model->sendCommand(parser);
                    this->view->setStartRound(false);
                        }
                else if(this->view->exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->exchange_button.playSound();
                    GameInputParser parser("/exchange");
                    this->model->sendCommand(parser);
                    this->view->setStartRound(false);
                        }
                else if(this->view->roll_dice_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->roll_dice_button.playSound();
                    GameInputParser parser("/roll");
                    this->model->sendCommand(parser);
                    this->view->setStartRound(false);
                        }}
            else if (this->view->button_mode == "empty_cell"){
                if(this->view->buy_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->buy_button.playSound();
                    GameInputParser parser("/yes");
                    this->model->sendCommand(parser);
                    this->view->setCellRound(false);
                        }
                else if(this->view->no_buy_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->no_buy_button.playSound();
                    GameInputParser parser("/no");
                    this->model->sendCommand(parser);
                    this->view->setCellRound(false);
                        }}
            else if (this->view->button_mode == "specard_cell"){
                if(this->view->paid_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->paid_button.playSound();
                    GameInputParser parser("/pay");
                    this->model->sendCommand(parser);
                    this->view->setCardSpeRound(false);
                        }
                else if(this->view->draw_card_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->draw_card_button.playSound();
                    GameInputParser parser("/card");
                    this->model->sendCommand(parser);
                    this->view->setCardSpeRound(false);
                        }}
            else if (this->view->button_mode == "on_prison"){
                if(this->view->paid_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->paid_prison_button.playSound();
                    GameInputParser parser("/pay");
                    this->model->sendCommand(parser);
                    this->view->setPrisonRound(false);
                        }
                else if(this->view->roll_dice_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->roll_dice_prison_button.playSound();
                    GameInputParser parser("/roll");
                    this->model->sendCommand(parser);
                    this->view->setPrisonRound(false);
                        }
                else if(this->view->card_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->card_prison_button.playSound();
                    GameInputParser parser("/use");
                    this->model->sendCommand(parser);
                    this->view->setPrisonRound(false);
                        }}
            else if (this->view->button_mode == "exchange_round"){
                if(this->view->yes_exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->yes_exchange_button.playSound();
                    GameInputParser parser("/accept");
                    this->model->sendCommand(parser);
                    this->view->setExchangeRound(false);
                        }
                else if(this->view->no_exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->no_exchange_button.playSound();
                    GameInputParser parser("/refuse");
                    this->model->sendCommand(parser);
                    this->view->setExchangeRound(false);
                        }}
            else if (this->view->button_mode == "bankrupt_round"){
                if(this->view->sell_bankrupt_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->sell_button.playSound();
                    GameInputParser parser("/sell");
                    this->model->sendCommand(parser);
                    this->view->setBankruptRound(false);
                        }
                else if(this->view->mortgage_bankrupt_button.contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->mortgage_button.playSound();
                    GameInputParser parser("/mortgage");
                    this->model->sendCommand(parser);
                    this->view->setBankruptRound(false);
                        }}
            else if (this->view->button_mode == "auction_round"){
                if(this->view->auction_box.getUpButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->auction_box.upNumber();
                        }
                else if(this->view->auction_box.getDownButton()->contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                    this->view->auction_box.downNumber();    
                        }
                else if(this->view->auction_box.getValidateButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                    this->view->message_box.setString(std::to_string(this->view->auction_box.getValidateNumber()));
                    GameInputParser parser("/bid " + std::to_string(this->view->auction_box.getValidateNumber()));
                    this->model->sendCommand(parser);
                    this->view->setAuctionRound(false);
                        }
                else if(this->view->auction_box.getLeaveButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                    GameInputParser parser("/out");
                    this->model->sendCommand(parser);
                    this->view->setAuctionRound(false);
                        }}
            else if(this->view->button_mode == "end_round"){
                 if(this->view->leave_button_end.contains(event.mouseButton.x, event.mouseButton.y)){
                        GameInputParser parser("/quit");
                        this->model->sendCommand(parser);
                        this->view->setEnd(false);
                        this->new_state = STATE::MENU;}}
            if(this->view->board_click == true){
                if (this->view->exchange_mode == true){
                    if(this->view->exchange_box.getUpButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                        this->view->exchange_box.upNumber();}
                    else if(this->view->exchange_box.getDownButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                        this->view->exchange_box.downNumber();}
                    else if(this->view->exchange_box.getLeaveButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                        GameInputParser parser("/leave");
                        this->model->sendCommand(parser);
                        this->view->board.unsetAllGrayed();
                        this->view->setBoardClickMode(false);
                        this->view->exchange_mode = false;
                        this->view->setStartRound(true);}}

                else if(this->view->other_mode == true){
                    if(this->view->leave_button.contains(event.mouseButton.x, event.mouseButton.y)){
                        GameInputParser parser("/leave");
                        this->model->sendCommand(parser);
                        this->view->board.unsetAllGrayed();
                        this->view->setBoardClickMode(false);
                        this->view->other_mode = false;
                        this->view->setStartRound(true);}
                }
                for(auto& i : *(this->view->board.getBoardButton())){
                    if(i->getButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                        if (this->view->exchange_mode == true){
                            GameInputParser parser("/trade " +  this->view->board.getCellName(i->getCellNumber())+ " " + std::to_string(this->view->exchange_box.getValidateNumber()));
                            this->model->sendCommand(parser);
                            this->view->exchange_mode = false;
                        }
                        else if(this->view->other_mode == true){
                            GameInputParser parser("/select " +  this->view->board.getCellName(i->getCellNumber()));
                            this->model->sendCommand(parser);
                            this->view->other_mode = false;
                        }
                        this->view->setBoardClickMode(false);
                    }}
                }}


void GameGUIController::receiveMsgLoop() {
    while (this->new_state == STATE::GAME){
       
        std::string response;
        QUERY query = this->model->receive(response);

        switch(query) {
            case QUERY::PLAYER_CREATE_GAME :            this->createGameGU(response); break;
            case QUERY::PLAYER_JOIN_GAME :              this->joinGameGU(response);break;
            case QUERY::INFOS_START :                   this->infoStartGU(response); break;
            case QUERY::INFOS_NOT_STARTED :             this->view->message_box.setString("Pour demarrer la partie, appuie sur start)"); break;
            case QUERY::INFOS_CANNOT_START :            this->view->message_box.setString("Attend tes amis avant de lancer la partie !"); this->view->setStartGame(true);break;
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
            case QUERY::INFOS_PLAYER_LOSE_MONEY :       this->loseMoneyGU(response);break;
            case QUERY::INFOS_CARD_CELL_TO_GO :         this->cardCellToGoGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL :this->moveOnCardCellGU(response); break;
            case QUERY::INFOS_CARD_DESCRIPTION :        this->drawCardGU(response); break;
            case QUERY::INFOS_DOUBLE_TURN:              this->doubleTurnGU(response);break;
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

            case QUERY::INFOS_AUCTION_START :           this->startAuctionGU(response); break;
            case QUERY::INFOS_AUCTION_BID :             this->auctionBidGU(response); break;
            case QUERY::INFOS_AUCTION_END :             this->endAuctionGU(response); break;
            case QUERY::WAIT_YOUR_TURN :                this->view->message_box.setString("Votre tour d'enchère a prit fin, attendez le suivant."); break;
            case QUERY::BAD_AMOUNT :                    this->view->message_box.setString("Le montant entre n'est pas correct"); break;
            case QUERY::NOT_ENOUGH_MONEY_TO_PARTICIPATE:      this->view->message_box.setString("Vous n'avez plus assez d'argent pour continuer a participer."); break;
            case QUERY::LEAVE_BID:                      this->view->message_box.setString("Vous avez abandonne les encheres"); break;
            case QUERY::YOUR_AUCTION_TURN:              break;
    

            case QUERY::INFOS_PLAYER_DIDNT_BUY :        if (response != this->model->getUsername()) { this->view->message_box.setString("Le joueur " + response + " n'a pas achete la propriete"); } break;
            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL : if (this->model->isMyTurn()) { this->view->message_box.setString("Vous etes chez vous."); } break;
            case QUERY::BAD_COMMAND :                   if (this->model->isMyTurn()) { this->view->message_box.setString("Vous ne pouvez pas utiliser cette commande"); } break;

            case QUERY::CHOICE_MONEY_CARD :             this->view->setCardSpeRound(true); break;
            case QUERY::NO_BUILDABLE_PROP :             this->view->message_box.setString("Vous n\'avez pas de terrain pouvant avoir de nouveaux batiments"); this->view->setStartRound(true);break;
            case QUERY::NO_SALABLE_PROP :               this->view->message_box.setString("Vous n\'avez pas de terrain pouvant etre vendu"); this->view->setStartRound(true);break;
            case QUERY::NO_MORTGAGEABLE_PROP :          this->view->message_box.setString("Vous n\'avez pas de terrain pouvant etre hypoteque"); this->view->setStartRound(true);break;
            case QUERY::NO_UNMORTGAGEABLE_PROP :        this->view->message_box.setString("Vous n\'avez pas de terrain pouvant etre deshypotheque"); this->view->setStartRound(true);break;
            case QUERY::NO_EXCHANGEABLE_PROP :			this->view->message_box.setString("Il n'y a pas de terrain disponible a l'echange");this->view->setStartRound(true); break;

            case QUERY::CANNOT_BUILD :                  {this->view->other_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("Ce terrain ne peut pas acceuillir de nouveaux batiments"); 
                                                        break;}
            case QUERY::CANNOT_SELL :                   {this->view->other_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("Ce terrain ne peut pas perdre des batiments"); 
                                                        break;}
            case QUERY::CANNOT_MORTAGE :                {this->view->other_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("Ce terrain ne peut pas etre hypotheque");
                                                        break;}
            case QUERY::CANNOT_UNMORTGAGE :             {this->view->other_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("Ce terrain ne peut pas etre deshypotheque"); 
                                                        break;}
            case QUERY::CANNOT_EXCHANGE :				{this->view->exchange_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("Ce terrain ne peut pas etre echange"); 
                                                        break;}

            case QUERY::EXCHANGE_REFUSED :              {this->view->exchange_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("L'echange a ete refuse"); break;}
            case QUERY::INFOS_NOT_ENOUGH_MONEY :        this->view->message_box.addString("Vous ne possedez pas assez d'argent."); break;
            case QUERY::INFOS_AUTO_OTHER_POSSIBILITY:   this->view->message_box.setString("L'autre possibilite a ete automatiquement selectionnee"); break;
            case QUERY::STOP_WAIT :                     this->view->message_box.setString("Pas assez rapide. L'offre a été automatiquement annulee"); break;
                                                       
            
            case QUERY::INFOS_DEBT :                    this->debtModeGU(response);break;
            case QUERY::INFOS_WON_LAND :                this->wonLandGU(response); break;

            case QUERY::WIN :                           this->endGameGU(response); break;
            case QUERY::ENDGAME :                       break;

            case QUERY::GAME_TIME_EXPIRED:              this->view->message_box.setString("IL N'Y A PLUS DE TEMPS, LA PARTIE SE TERMINE");break;
            
            
            default :                                   this->view->message_box.setString(response);break;
        }
    }
}

void GameGUIController::playerJoinUpdate(std::string new_player){ 
    this->view->lobby.newPlayerJoin(new_player);
    this->view->message_box.addString("Un joueur a rejoint le lobby: "+new_player);
}

void GameGUIController::update() { this->initGame();}

void GameGUIController::initGame() {
    // create a thread to receive messages
    std::thread send_thread(&GameGUIController::receiveMsgLoop, this);
    send_thread.detach();
}


void GameGUIController::initScreen(int gamecode) {
    if (!init) return;
    this->view->endTurn();
    if ( this->model->isCreator() ) {
        this->view->gamecode_box.setVisible();
        this->view->gamecode_box.setGamecode(gamecode);
        this->view->message_box.setString("Vous etes le proprietaire de cette partie");
        this->view->message_box.addString("utilisez /start pour lancer la partie");
        this->view->setStartGame(true);
    }
    else {
        this->view->gamecode_box.setVisible();
        this->view->gamecode_box.setGamecode(gamecode);
        this->view->message_box.setString("En attente du lancement de la partie...");
    }
    init = false;
}


void GameGUIController::startGame(int beginner) {
    this->view->startingGame = true; //caché le lobby ici
    this->view->message_box.clearText();
    this->model->setPlayerTurn( game_info->player_usernames[beginner]);
    if (this->model->getUsername() ==  game_info->player_usernames[beginner]) {
        this->view->startTurn();
        this->model->startTurn();
        //rajouter sons - début game
    }

    
    else{ this->view->message_box.setString("C'est au tour de " +  game_info->player_usernames[beginner] + " !");}

    
    this->view->gamecode_box.setHidden();
    this->view->logo.setVisible();
    this->view->board.setColorNumber(game_info->nb_player);
    this->view->info_box.initMoney(game_info->nb_player,game_info->start_money);
    this->view->info_box.initJailcard(game_info->nb_player,0);
    for (int i = 0; i< game_info->nb_player; i++) {
        this->view->board.setPlayer(0, i);
        this->view->info_box.setPseudo(i, game_info->player_usernames[i]);}

}




//////////////////////////////////////////////////////// 


void GameGUIController::createGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    game_info = launching_parser.parseCreateQuery();
    this->model->createGame();
    this->initScreen(game_info->game_code);
}


void GameGUIController::joinGameGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    game_info = launching_parser.parseJoinQuery();
    std::string new_player = game_info->username;
    this->initScreen(game_info->game_code);
    this->playerJoinUpdate(new_player);
}


void GameGUIController::infoStartGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<StartInfo> start_info = launching_parser.parseStartQuery();
    game_info->nb_player = start_info->player_nb;
    game_info->player_usernames = start_info->player_usernames;
    this->view->message_box.setString("La partie commence");
    this->startGame(start_info->beginner);
}

void GameGUIController::rollDiceGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<RollDiceInfo> dice_info = game_parser.parseRollDiceQuery();
    if (this->model->isMyTurn()){
        this->view->dice.setDice(dice_info->first_value,dice_info->second_value);
        this->view->message_box.addString("Vous avez obtenu un " + std::to_string(dice_info->first_value) + " et un " + std::to_string(dice_info->second_value));}  
    else {
        this->view->message_box.addString("Le joueur " + this->model->getPlayerTurn() + " a obtenu un " + std::to_string(dice_info->first_value ) + " et un " + std::to_string(dice_info->second_value));}
        
}


void GameGUIController::infoGameGU(const std::string& response) {
    InGameParser game_parser(response);
    std::shared_ptr<std::vector<GameInfo>> player_game_info = game_parser.parseInfosGameQuery(game_info->nb_player);
    for (int i = 0; i < game_info->nb_player; i++){
        this->view->board.movePlayer(player_game_info->at(i).position, i);}}


void GameGUIController::newTurnGU(const std::string& response) {
    this->model->setPlayerTurn(response);
    this->view->card_text.setString("");
    if (response == this->model->getUsername()) { 
        this->view->startTurn(); 
        this->model->startTurn();
        this->view->setStartRound(true);
    }
    else { 
        this->view->endTurn(); 
        this->model->endTurn(); 
        this->view->message_box.addString("C'est au tour de " + response + " !"); }}


void GameGUIController::doubleTurnGU(const std::string& response) {
    if (this->model->isMyTurn()) { this->view->startTurn(); }
    else { this->view->message_box.setString(response + " va relancer les dés !"); }
}


void GameGUIController::newTurnInJailGU(const std::string& response) {
    JailInfo jail_info(response);
    this->view->message_box.setString("Vous etes en prison depuis " + std::to_string(jail_info.nb_turn) + " tours !");
    this->view->setPrisonRound(true);
    if (jail_info.has_card == false){this->view->card_prison_button.setHidden();}
}



void GameGUIController::playerMoveGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->board.getCellIndex(move_info->property_name);
    this->view->board.movePlayer(index, move_info->player - 1);
    if (move_info->property_name == "Prison" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez sur la prison.");
    } else if (move_info->property_name == "Start" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez sur la case depart.");
    } else if (move_info->property_name == "Parc" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez au parc gratuit.");
    }
}

void GameGUIController::playerBoughtGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    int index = this->view->board.getCellIndex(move_info->property_name);
    this->view->board.setPurchased(index, move_info->player - 1);
    this->view->info_box.setMoney(move_info->player - 1, move_info->player_money); 
}


void GameGUIController::playerPaidPlayerGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerPaidPlayerInfo> payement_info = game_parser.parsePlayerPaidPlayerQuery();
    if (this->model->isMyTurn()) {
        this->view->info_box.setMoney(payement_info->loser - 1, payement_info->loser_money);
        this->view->info_box.setMoney(payement_info->winner - 1, payement_info->winner_money);
        this->view->message_box.setString("Vous devez " + std::to_string(payement_info->amount) + "$ a " + game_info->player_usernames[payement_info->winner-1] + " :");
    } else {
        this->view->message_box.setString( game_info->player_usernames[payement_info->loser-1] + " doit " + std::to_string(payement_info->amount) + "$ a " +  game_info->player_usernames[payement_info->winner-1] + " :");
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
    this->view->board.movePlayer(index, tax_info->player-1);
    this->view->info_box.setMoney(tax_info->player - 1, tax_info->player_money);
    if (this->model->isMyTurn()) {
        this->view->message_box.setString("Vous arrivez sur la case " + tax_info->tax_name + " :");
    } else {
        this->view->message_box.setString( game_info->player_usernames[tax_info->player - 1] + " paie ses taxes : ");
    }

}

void GameGUIController::goOutPrisonGU(const std::string& response){
    if (this->model->isMyTurn()){ this->view->message_box.setString("Vous sortez de prison.");
    } else this->view->message_box.setString(response + "sort de prison.");
}

void GameGUIController::sendPrisonGU(const std::string& response){
    if (this->model->isMyTurn()){this->view->message_box.addString("Vous etes envoye en prison.");
    } else this->view->message_box.setString(response + " a ete envoye en prison.");
}

void GameGUIController::getGoOutJailCardGU(const std::string& response){
    this->view->info_box.addJailCard(atoi(response.c_str())-1);
    if (this->model->isMyTurn()){ 
        this->view->message_box.setString("Vous obtenez une carte sortie de prison.");
    } else this->view->message_box.setString( game_info->player_usernames[atoi(response.c_str())] + "a obtenu une carte sortie de prison.");
}


void GameGUIController::loseGoOutJailCardGU(const std::string& response){
    this->view->info_box.removeJailCard(atoi(response.c_str()));
    if (this->model->isMyTurn()) this->view->message_box.setString("Vous utilisez votre carte.");
}

void GameGUIController::wonMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->info_box.setMoney(money_info->player - 1, money_info->player_money);
    if (! this->model->isMyTurn()) { 
        this->view->message_box.setString( game_info->player_usernames[money_info->player-1] + " a gagne " + std::to_string(money_info->amount) + "$"); }
    else { 
        if ( game_info->player_usernames[money_info->player-1] == this->model->getUsername()){
            this->view->message_box.setString("Vous gagnez " + std::to_string(money_info->amount) + "$");
        }
        else this->view->message_box.setString( game_info->player_usernames[money_info->player-1] + " gagne " + std::to_string(money_info->amount) + "$");
    }
}

void GameGUIController::loseMoneyGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    this->view->info_box.setMoney(money_info->player - 1, money_info->player_money);
    if (! this->model->isMyTurn()) this->view->message_box.setString( game_info->player_usernames[money_info->player-1] + " a perdu " + std::to_string(money_info->amount) + "$");
    else { 
        if ( game_info->player_usernames[money_info->player-1] == this->model->getUsername()){
            this->view->message_box.setString("Vous perdez " + std::to_string(money_info->amount) + "$"); 
        }
        else this->view->message_box.setString( game_info->player_usernames[money_info->player-1] + " perd " + std::to_string(money_info->amount) + "$");
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
    this->view->board.movePlayer(move_cardcell_info->new_pos, move_cardcell_info->player - 1 );
    if (this->model->isMyTurn()){
        this->view->message_box.setString("Vous venez de piocher une carte :");
        this->view->card_title.setHidden();
        this->view->dice.setVisible();
        this->view->card_text.setVisible();
        this->view->card_text.setString(move_cardcell_info->description);

    } 
    else {
        this->view->message_box.setString( game_info->player_usernames[move_cardcell_info->player - 1] + " pioche un carte.");
}
}

void GameGUIController::drawCardGU(const std::string& response){
    this->view->message_box.setString("Vous venez de piocher une carte :" + response);}


void GameGUIController::buildPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->setSpeRound(true);
        this->view->other_mode = true;
        this->view->board.setAllGrayed();
        for (auto& property : selection_mode){
            int index = this->view->board.getCellIndex(property);
            this->view->board.setBuildable(index);
        }
    } else this->view->message_box.setString("Consultation des batiments a construire...");
}

void GameGUIController::sellPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->setSpeRound(true);
        this->view->other_mode = true;
        this->view->board.setAllGrayed();
        for (auto& property : selection_mode){
            int index = this->view->board.getCellIndex(property);
            this->view->board.setSalable(index);
        }
    } else this->view->message_box.setString("Consultation des proprietes a vendre ...");
}

void GameGUIController::exchangePropertyGU(const std::string& response){
    response.c_str();
    ExchangeInfo exchanges(response, game_info->nb_player);
    selection_mode = exchanges.all_properties;
    if (this->model->isMyTurn()){
        this->view->board_click= true;
        this->view->exchange_mode = true;
        this->view->exchange_box.setVisible();
        this->view->board.setAllGrayed();
        for (int i=0; i<game_info->nb_player; i++){
            for (auto& property : exchanges.player_properties.at(i)){
                int index = this->view->board.getCellIndex(property);
                this->view->board.setExchangeable(index);
            }
        }
    } else this->view->message_box.setString("Consultation des echanges ...");

}

void GameGUIController::mortgagePropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->setSpeRound(true);
        this->view->other_mode = true;
        this->view->board.setAllGrayed();
        for (auto& property : selection_mode){
            int index = this->view->board.getCellIndex(property);
            this->view->board.setMortgageable(index);
        }
    } else this->view->message_box.setString("Consultation des proprietes a hypotequer ...");
}

void GameGUIController::unmortgagePropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    if (this->model->isMyTurn()){
        this->view->setSpeRound(true);
        this->view->other_mode = true;
        this->view->board.setAllGrayed();
        for (auto& property : selection_mode){
            int index = this->view->board.getCellIndex(property);
            this->view->board.setUnmortgageable(index);
        }
    } else this->view->message_box.setString("Consultation des proprietes a deshypotequer ...");
}

void GameGUIController::leaveSelectionMenuGU(const std::string& response){
    for (auto& property : selection_mode) {
        int index = this->view->board.getCellIndex(property);
        this->view->board.leaveSelection(index);
    }
    this->view->board.unsetAllGrayed();
}


void GameGUIController::buildOrSellSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    this->view->setSpeRound(true);
    this->view->other_mode = true;
    int index = this->view->board.getCellIndex(success_info->name);
    this->view->board.setHouse(index, success_info->level);
    this->view->board.leaveSelection(index);
}

void GameGUIController::mortgageSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    this->view->setSpeRound(true);
    this->view->other_mode = true;
    int index = this->view->board.getCellIndex(success_info->name);
    this->view->board.setMortgaged(index);
}

void GameGUIController::unmortgageSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    this->view->setSpeRound(true);
    this->view->other_mode = true;
    int index = this->view->board.getCellIndex(success_info->name);
    this->view->board.unmortgage(index);
}


void GameGUIController::exchangeSucceedGU(const std::string & response){
	ExchangeSucceedInfo succeed(response);
	int index = this->view->board.getCellIndex(succeed.property);
    if (this->model->isMyTurn()){
        this->view->exchange_mode = true;
        this->view->setBoardClickMode(true);
        this->view->board.leaveSelection(index); 
	    this->view->board.setPurchased(index, succeed.player -1);}
}

void GameGUIController::askExchangeGU(const std::string & response){
    AskExchangeInfo exchange_info(response);
    this->view->message_box.setString(exchange_info.username + " aimerait vous racheter " + exchange_info.property + " pour " + std::to_string(exchange_info.price) +"$");
    this->view->setExchangeRound(true);
}

void GameGUIController::confirmExchangeAskingGU(const std::string& response){
    AskExchangeInfo exchange_info(response);
    this->view->message_box.setString("La demande de rachat de " + exchange_info.property + " pour " + std::to_string(exchange_info.price) + "$ a ete envoyee a " + exchange_info.username);
}

void GameGUIController::askForPurchaseGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<AskForPurchaseInfo> purchase = game_parser.parseAskForPurchaseQuery();
    this->view->message_box.setString("Acheter " + purchase->cell_name + " pour " + std::to_string(purchase->amount)+"$ ?");
    this->view->setCellRound(true);
    this->view->message_box.addString("Si vous ne l'achetez pas, des encheres debuteront");
}


void GameGUIController::startAuctionGU(const std::string& response){
    BetInfo bet(response);
    this->view->message_box.setString("Des encheres pour acheter " + bet.property + " debutent !");
}

void GameGUIController::auctionBidGU(const std::string& response){
    PlayerBetInfo bet(response);
    if (bet.player != ""){
        this->view->message_box.setString(bet.player + " est sur le point d'acheter le terrain pour : " + std::to_string(bet.amount) + "$");
    }
    else this->view->message_box.setString( "Le prix de depart est : " + std::to_string(bet.amount) + "$ !");
    if (! this->model->isMyTurn()){
        this->view->message_box.setString("valider pour surencherir !");
        this->view->setAuctionRound(true);
        this->view->auction_box.setTextNumber(bet.amount);
        this->view->auction_box.setAuctionLimit(bet.amount);
        }  
}

void GameGUIController::endAuctionGU(const std::string& response){
   EndAuctionInfo end(response);
    if (end.player != ""){
        this->view->message_box.setString(end.player + " remporte " + end.property + " pour " + std::to_string(end.amount) + "$ !");
    }
    else this->view->message_box.setString("Personne ne remporte " + end.property + ".");}

void GameGUIController::endGameGU(const std::string& response){
    this->view->message_box.setString("Victoire de " + response + ". Félicitations !");
    this->view->endTurn();
    this->view->setEnd(true);
}

void GameGUIController::wonLandGU(const std::string& response){
    WonLand won_land(response);
    int index = this->view->board.getCellIndex(won_land.land);
    this->view->board.setPurchased(index, won_land.player - 1);
}

void GameGUIController::debtModeGU(const std::string& response){
    if(this->model->isMyTurn()){
        this->view->message_box.setString("c'est la hess, que voulez vous faire");
        this->view->setBankruptRound(true);
    }
}
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
                    GameInputParser parser("/card");
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
                if(this->view->sell_bankrupt_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->give_up_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "participate_round"){
                if(this->view->participate_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
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
                    GameInputParser parser("/bid " + this->view->auction_box.getValidateNumber());
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
                        std::cout << "clicked" << std::endl;
                        this->model->sendCommand(parser);
                        this->new_state = STATE::MENU;}
            }
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
                        std::cout << "clicked" << std::endl;
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
        std::cout << "->" << response << std::endl;

        switch(query) {
            case QUERY::PLAYER_CREATE_GAME :            std::cout<<"&&"<<"a"<<std::endl;this->createGameGU(response); break;
            case QUERY::PLAYER_JOIN_GAME :              std::cout<<"&&"<<"b"<<std::endl;this->joinGameGU(response);break;
            case QUERY::INFOS_START :                   std::cout<<"&&"<<"c"<<std::endl;this->infoStartGU(response); break;
            case QUERY::INFOS_NOT_STARTED :             std::cout<<"&&"<<"d"<<std::endl;this->view->message_box.setString("Pour demarrer la partie, appuie sur start)"); break;
            case QUERY::INFOS_CANNOT_START :            std::cout<<"&&"<<"e"<<std::endl;this->view->message_box.setString("Attend tes amis avant de lancer la partie !"); this->view->setStartGame(true);break;
            case QUERY::INFOS_ROLL_DICE :               std::cout<<"&&"<<"f"<<std::endl;this->rollDiceGU(response); break;
            case QUERY::INFOS_GAME :                    //std::cout<<"&&"<<"g"<<std::endl;this->infoGameGU(response); break;
            case QUERY::INFOS_NEW_TURN :                std::cout<<"&&"<<"h"<<std::endl;this->newTurnGU(response); break;
            case QUERY::INFOS_NEW_TURN_IN_JAIL:         std::cout<<"&&"<<"i"<<std::endl;this->newTurnInJailGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE :             std::cout<<"&&"<<"j"<<std::endl;std::cout<<"move"<<std::endl;this->playerMoveGU(response); break;
            case QUERY::INFOS_PLAYER_BOUGHT :           std::cout<<"&&"<<"k"<<std::endl;;this->playerBoughtGU(response); break;
            case QUERY::INFOS_PLAYER_PAID_PLAYER :      std::cout<<"&&"<<"l"<<std::endl;this->playerPaidPlayerGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL: std::cout<<"&&"<<"m"<<std::endl;this->moveOnMortgagedCellGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_TAX_CELL : std::cout<<"&&"<<"n"<<std::endl;this->moveOnTaxCellGU(response); break;
            case QUERY::INFOS_PLAYER_GO_OUT_PRISON :    std::cout<<"&&"<<"o"<<std::endl;this->goOutPrisonGU(response); break;
            case QUERY::INFOS_PLAYER_SEND_TO_PRISON :   std::cout<<"&&"<<"p"<<std::endl;this->sendPrisonGU(response); break;
            case QUERY::GET_GO_OUT_JAIL_CARD :          std::cout<<"&&"<<"q"<<std::endl;this->getGoOutJailCardGU(response); break;
            case QUERY::LOST_GO_OUT_JAIL_CARD :         std::cout<<"&&"<<"r"<<std::endl;this->loseGoOutJailCardGU(response); break;
            case QUERY::INFOS_PLAYER_WON_MONEY :        std::cout<<"&&"<<"s"<<std::endl;this->wonMoneyGU(response); break;
            case QUERY::INFOS_PLAYER_LOSE_MONEY :       std::cout<<"&&"<<"t"<<std::endl;this->loseMoneyGU(response);break;
            case QUERY::INFOS_CARD_CELL_TO_GO :         std::cout<<"&&"<<"u"<<std::endl;this->cardCellToGoGU(response); break;
            case QUERY::INFOS_PLAYER_MOVE_ON_CARD_CELL :std::cout<<"&&"<<"v"<<std::endl;this->moveOnCardCellGU(response); break;
            case QUERY::INFOS_CARD_DESCRIPTION :        std::cout<<"&&"<<"w"<<std::endl;this->drawCardGU(response); break;
            case QUERY::INFOS_DOUBLE_TURN:              this->doubleTurnGU(response);break;
            case QUERY::USELESS_MESSAGE :               std::cout<<"&&"<<"x"<<std::endl; break;

            case QUERY::INFOS_BUILD_PROP :              std::cout<<"&&"<<"y"<<std::endl;this->buildPropertyGU(response); break;
            case QUERY::INFOS_SELL_BUILD :              std::cout<<"&&"<<"z"<<std::endl;this->sellPropertyGU(response); break;
            case QUERY::INFOS_MORTGAGEABLE_PROP :       std::cout<<"&&"<<"A"<<std::endl;this->mortgagePropertyGU(response); break;
            case QUERY::INFOS_LIFT_MORTGAGEABLE_PROP :  std::cout<<"&&"<<"B"<<std::endl;this->unmortgagePropertyGU(response); break;
            case QUERY::INFOS_EXCHANGEABLE_PROP :       std::cout<<"&&"<<"C"<<std::endl;this->exchangePropertyGU(response); break;            
            case QUERY::INFOS_LEAVE_SELECTION_MODE :    std::cout<<"&&"<<"D"<<std::endl;this->leaveSelectionMenuGU(response); break;

            case QUERY::INFOS_BUILD_SUCCESS :
            case QUERY::INFOS_SELL_BUILD_SUCCESS :      std::cout<<"&&"<<"E"<<std::endl;this->buildOrSellSucceedGU(response); break;
            case QUERY::INFOS_MORTGAGE_SUCCESS :        std::cout<<"&&"<<"F"<<std::endl;this->mortgageSucceedGU(response); break;
            case QUERY::INFOS_LIFT_MORTGAGE_SUCCESS :   std::cout<<"&&"<<"G"<<std::endl;this->unmortgageSucceedGU(response); break;
			case QUERY::INFOS_EXCHANGE_SUCCESS : 		std::cout<<"&&"<<"H"<<std::endl;this->exchangeSucceedGU(response); break;

            case QUERY::INFOS_ASK_FOR_PURCHASE :        std::cout<<"&&"<<"I"<<std::endl;this->askForPurchaseGU(response); break;
            case QUERY::ASK_EXCHANGE :                  std::cout<<"&&"<<"J"<<std::endl;this->askExchangeGU(response); break;
            case QUERY::CONFIRM_EXCHANGE_ASKING :       std::cout<<"&&"<<"K"<<std::endl;this->confirmExchangeAskingGU(response); break;

            case QUERY::INFOS_AUCTION_START :           std::cout<<"&&"<<"L"<<std::endl;this->startAuctionGU(response); break;
            case QUERY::INFOS_AUCTION_BID :             std::cout<<"&&"<<"M"<<std::endl;this->auctionBidGU(response); break;
            case QUERY::INFOS_AUCTION_END :             std::cout<<"&&"<<"N"<<std::endl;this->endAuctionGU(response); break;
            case QUERY::WAIT_YOUR_TURN :                std::cout<<"&&"<<"O"<<std::endl;this->view->message_box.setString("Votre tour d'enchère a prit fin, attendez le suivant."); break;
            case QUERY::BAD_AMOUNT :                    std::cout<<"&&"<<"P"<<std::endl;this->view->message_box.setString("Le montant entre n'est pas correct"); break;
            case QUERY::NOT_ENOUGH_MONEY_TO_PARTICIPATE:std::cout<<"&&"<<"Q"<<std::endl;this->view->message_box.setString("Vous n'avez plus assez d'argent pour continuer a participer."); break;
            case QUERY::LEAVE_BID:                      std::cout<<"&&"<<"R"<<std::endl;std::cout<<"&&"<<"a"<<std::endl;this->view->message_box.setString("Vous avez abandonne les encheres"); break;

            case QUERY::INFOS_PLAYER_DIDNT_BUY :        std::cout<<"&&"<<"S"<<std::endl;if (response != this->model->getUsername()) { this->view->message_box.setString("Le joueur " + response + " n'a pas achete la propriete"); } break;
            case QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL : std::cout<<"&&"<<"T"<<std::endl;if (this->model->isMyTurn()) { this->view->message_box.setString("Vous etes chez vous."); } break;
            case QUERY::BAD_COMMAND :                   std::cout<<"&&"<<"U"<<std::endl;if (this->model->isMyTurn()) { this->view->message_box.setString("Vous ne pouvez pas utiliser cette commande"); } break;

            case QUERY::CHOICE_MONEY_CARD :             std::cout<<"&&"<<"V"<<std::endl;this->view->setCardSpeRound(true); break;
            case QUERY::NO_BUILDABLE_PROP :             std::cout<<"&&"<<"W"<<std::endl;this->view->message_box.setString("Vous n\'avez pas de terrain pouvant avoir de nouveaux batiments"); this->view->setStartRound(true);break;
            case QUERY::NO_SALABLE_PROP :               std::cout<<"&&"<<"X"<<std::endl;this->view->message_box.setString("Vous n\'avez pas de terrain pouvant etre vendu"); this->view->setStartRound(true);break;
            case QUERY::NO_MORTGAGEABLE_PROP :          std::cout<<"&&"<<"Y"<<std::endl;this->view->message_box.setString("Vous n\'avez pas de terrain pouvant etre hypoteque"); this->view->setStartRound(true);break;
            case QUERY::NO_UNMORTGAGEABLE_PROP :        std::cout<<"&&"<<"Z"<<std::endl;this->view->message_box.setString("Vous n\'avez pas de terrain pouvant etre deshypotheque"); this->view->setStartRound(true);break;
            case QUERY::NO_EXCHANGEABLE_PROP :			std::cout<<"&&"<<"1"<<std::endl;this->view->message_box.setString("Il n'y a pas de terrain disponible a l'echange");this->view->setStartRound(true); break;

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
            case QUERY::CANNOT_EXCHANGE :				{std::cout<<"&&"<<"6"<<std::endl;this->view->exchange_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("Ce terrain ne peut pas etre echange"); 
                                                        break;}

            case QUERY::EXCHANGE_REFUSED :              {std::cout<<"&&"<<"7"<<std::endl;this->view->exchange_mode = true;
                                                        this->view->setBoardClickMode(true);
                                                        this->view->message_box.setString("L'echange a ete refuse"); break;}
            case QUERY::INFOS_NOT_ENOUGH_MONEY :        std::cout<<"&&"<<"8"<<std::endl;this->view->message_box.addString("Vous ne possedez pas assez d'argent."); break;
            case QUERY::INFOS_AUTO_OTHER_POSSIBILITY:   std::cout<<"&&"<<"9"<<std::endl;this->view->message_box.setString("L'autre possibilite a ete automatiquement selectionnee"); break;
            case QUERY::STOP_WAIT :                     {std::cout<<"&&"<<"10"<<std::endl;this->view->message_box.setString("Pas assez rapide. L'offre a été automatiquement annulee"); 
                                                        if (this->model->isMyTurn()){this->view->setStartRound(true);}
                                                        break;}
            
            case QUERY::INFOS_DEBT :                    std::cout<<"&&"<<"11"<<std::endl;break;
            case QUERY::INFOS_WON_LAND :                std::cout<<"&&"<<"12"<<std::endl;this->wonLandGU(response); break;

            case QUERY::WIN :                           std::cout<<"&&"<<"13"<<std::endl;this->endGameGU(response); break;
            case QUERY::ENDGAME :                       std::cout<<"&&"<<"14"<<std::endl;break;
            
            
            default :                                   std::cout << "defaut ? " << std::endl;this->view->message_box.setString(response);break;
        }
    }
}

void GameGUIController::playerJoinUpdate(){ 
    //this->view->getInfo()->setPlayersInGame(game_info->player_usernames); à rajouter
     this->view->message_box.addString("Un joueur a rejoint le lobby");
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
    std::cout << "aaa " << std::endl;
    this->view->message_box.clearText();
    std::cout << "aaa2 " << std::endl;
    this->model->setPlayerTurn(players_username[beginner]);
    std::cout << "aaa3 " << std::endl;
    if (this->model->getUsername() == players_username[beginner]) {
        std::cout << "aaa4 " << std::endl;
        this->view->startTurn();
        this->model->startTurn();
        std::cout << "aaa5 " << std::endl;
        //rajouter sons - début game
    }
    
    else{ 
        std::cout << "aaa6 " << std::endl;
        this->view->message_box.setString("C'est au tour de " + players_username[beginner] + " !");
        std::cout << "aaa7 " << std::endl;}
    this->view->gamecode_box.setHidden();
    this->view->logo.setVisible();
    this->view->board.setColorNumber(player_nb);
    this->view->info_box.initMoney(player_nb,1500);
    this->view->info_box.initJailcard(player_nb,0);
    for (int i = 0; i< player_nb; i++) {
        std::cout << "b" << std::endl;
        this->view->board.setPlayer(0, i);
        this->view->info_box.setPseudo(i,players_username[i]);}
    std::cout << "bb" << std::endl;

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
    this->initScreen(game_info->game_code);
    this->playerJoinUpdate();
}


void GameGUIController::infoStartGU(const std::string& response) {
    GameLaunchingParser launching_parser(response);
    std::shared_ptr<StartInfo> start_info = launching_parser.parseStartQuery();
    std::cout << "start ok" << std::endl;
    player_nb = start_info->player_nb;
    std::cout << "start ok1" << std::endl;
    players_username = start_info->player_usernames;
    std::cout << "start ok2" << std::endl;
    this->view->message_box.setString("La partie commence");
    std::cout << "start ok3" << std::endl;
    this->startGame(start_info->beginner);
     std::cout << "start fin" << std::endl;
}

void GameGUIController::rollDiceGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<RollDiceInfo> dice_info = game_parser.parseRollDiceQuery();
    std::cout << "ça roule ?" << std::endl;
    if (this->model->isMyTurn()){
        std::cout << "ça roule a ?" << std::endl;
        this->view->dice.setDice(dice_info->first_value,dice_info->second_value);
         std::cout << "ça roule b ?" << std::endl;
        this->view->message_box.addString("Vous avez obtenu un " + std::to_string(dice_info->first_value) + " et un " + std::to_string(dice_info->second_value));}  
    else {
        std::cout << "ça roule c ?" << std::endl;
        this->view->message_box.addString("Le joueur " + this->model->getPlayerTurn() + " a obtenu un " + std::to_string(dice_info->first_value ) + " et un " + std::to_string(dice_info->second_value));
        std::cout << "ici?" << std::endl;}
}


void GameGUIController::infoGameGU(const std::string& response) {
    InGameParser game_parser(response);
    std::shared_ptr<std::vector<GameInfo>> player_game_info = game_parser.parseInfosGameQuery(player_nb);
    for (int i = 0; i < player_nb; i++){
        std::cout << "beforemove1" << std::endl;
        this->view->board.movePlayer(player_game_info->at(i).position, i);
        for (unsigned int j = 0; j < player_game_info->at(i).properties.size(); j++){
            int index = this->view->board.getCellIndex(player_game_info->at(i).properties[j].name);
            if (player_game_info->at(i).properties[j].level == 0){
                this->view->board.setPurchased(index, i);
            }
            else this->view->board.setHouse(index, player_game_info->at(i).properties[j].level);
        }
        this->view->info_box.setMoney(i, player_game_info->at(i).money);
        this->view->info_box.setJailCard(i, player_game_info->at(i).jail_card_nb);}}


void GameGUIController::newTurnGU(const std::string& response) {
    std::cout << "début de tour 0" << std::endl;
    this->model->setPlayerTurn(response);
    //this->view->dice.resetDice();
    std::cout << "début de tour ok" << std::endl;
    this->view->card_text.setString("");
    if (response == this->model->getUsername()) { 
        std::cout << "début de tour a" << std::endl;
        this->view->startTurn(); 
        this->model->startTurn();
        this->view->setStartRound(true);
    }
    else { 
        std::cout << "tour du joueur" << std::endl;
        this->view->endTurn(); 
        this->model->endTurn(); 
        this->view->message_box.addString("C'est au tour de " + response + " !"); 
        std::cout << "fin" << std::endl;}}


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
    std::cout << "aa" << std::endl;
    int index = this->view->board.getCellIndex(move_info->property_name);
    std::cout << "aa1" << std::endl;
    std::cout << move_info->player - 1 << std::endl;
    std::cout << move_info->player - 1 << std::endl;
    this->view->board.movePlayer(index, move_info->player - 1);
    std::cout << "aa11" << std::endl;
    if (move_info->property_name == "Prison" and this->model->isMyTurn()){
        std::cout << "aa2" << std::endl;
        this->view->message_box.setString("Vous visitez la prison.");
    } else if (move_info->property_name == "Start" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez sur la case depart.");
    } else if (move_info->property_name == "Parc" and this->model->isMyTurn()){
        this->view->message_box.setString("Vous arrivez au parc gratuit.");
    }
    std::cout << "aa3" << std::endl;
}

void GameGUIController::playerBoughtGU(const std::string& response){
    std::cout << "miaou" << std::endl; 
    InGameParser game_parser(response);
    std::cout << "chat" << std::endl; 
    std::shared_ptr<PlayerMoveInfo> move_info = game_parser.parsePlayerMoveQuery();
    std::cout << "achat" << std::endl; 
    int index = this->view->board.getCellIndex(move_info->property_name);
    std::cout << "achat" << std::endl;
    std::cout << "move_info->player"<< move_info->player <<    std::endl;
    this->view->board.setPurchased(index, move_info->player - 1);
    std::cout << "achat2" << std::endl;    
    this->view->info_box.setMoney(move_info->player - 1, move_info->player_money);
      std::cout << "achat3" << std::endl;  
}


void GameGUIController::playerPaidPlayerGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<PlayerPaidPlayerInfo> payement_info = game_parser.parsePlayerPaidPlayerQuery();
    std::cout << "paid" << std::endl;
    if (this->model->isMyTurn()) {
        this->view->info_box.setMoney(payement_info->loser - 1, payement_info->loser_money);
        this->view->info_box.setMoney(payement_info->winner - 1, payement_info->winner_money);
        this->view->message_box.setString("Vous devez " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
    } else {
        this->view->message_box.setString(players_username[payement_info->loser-1] + " doit " + std::to_string(payement_info->amount) + "$ a " + players_username[payement_info->winner-1] + " :");
    }
}

void GameGUIController::moveOnMortgagedCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::cout << "onMorg" << std::endl;
    std::shared_ptr<MoveMortgagedInfo> mortgaged_info = game_parser.parseMoveMortgagedQuery();
    this->view->message_box.setString(mortgaged_info->username + " est tombe sur une propriete hypotheque");
}

void GameGUIController::moveOnTaxCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveTaxInfo> tax_info = game_parser.parseMoveTaxQuery();
    int index = this->view->board.getCellIndex(tax_info->tax_name);
    std::cout << "beforemove" << std::endl;
    this->view->board.movePlayer(index, tax_info->player-1);
    this->view->info_box.setMoney(tax_info->player - 1, tax_info->player_money);
    if (this->model->isMyTurn()) {
        this->view->message_box.setString("Vous arrivez sur la case " + tax_info->tax_name + " :");
    } else {
         std::cout << "tax1" << std::endl;
        this->view->message_box.setString(players_username[tax_info->player - 1] + " paie ses taxes : ");
         std::cout << "tax2" << std::endl;
    }
    std::cout << "grrbaw" << std::endl;

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
    std::cout << "prison card" << std::endl;
    std::cout << atoi(response.c_str()) << std::endl;
    this->view->info_box.addJailCard(atoi(response.c_str()));
    std::cout << "prison card2" << std::endl;
    if (this->model->isMyTurn()){ this->view->message_box.setString("Vous obtenez une carte sortie de prison.");
    std::cout << "prison card3" << std::endl;
    } else this->view->message_box.setString(players_username[atoi(response.c_str())] + "a obtenu une carte sortie de prison.");
    std::cout << "prison car4" << std::endl;
}


void GameGUIController::loseGoOutJailCardGU(const std::string& response){
    this->view->info_box.removeJailCard(atoi(response.c_str()));
    if (this->model->isMyTurn()) this->view->message_box.setString("Vous utilisez votre carte.");
}

void GameGUIController::wonMoneyGU(const std::string& response){
    std::cout << "la moula" << std::endl;
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    std::cout << "la moula1" << std::endl;
    this->view->info_box.setMoney(money_info->player - 1, money_info->player_money);
    std::cout << "la moula2" << std::endl;
    if (! this->model->isMyTurn()) { 
        std::cout << "la moula3" << std::endl;
        this->view->message_box.setString(players_username[money_info->player-1] + " a gagne " + std::to_string(money_info->amount) + "$");
        std::cout << "la moula4" << std::endl; }
    else { 
        std::cout << "la moula5" << std::endl;
        if (players_username[money_info->player-1] == this->model->getUsername()){
            std::cout << "la moula6" << std::endl;
            this->view->message_box.setString("Vous gagnez " + std::to_string(money_info->amount) + "$");
             std::cout << "la moula7" << std::endl;
        }
        else this->view->message_box.setString(players_username[money_info->player-1] + " gagne " + std::to_string(money_info->amount) + "$");
        std::cout << "la moula8" << std::endl;
    }
}

void GameGUIController::loseMoneyGU(const std::string& response){
    std::cout << "la rue" << std::endl;
    InGameParser game_parser(response);
    std::shared_ptr<WonOrLoseMoneyInfo> money_info = game_parser.parseWonOrLoseMoneyQuery();
    std::cout << money_info->player << "  gggg "  << money_info->player_money << std::endl;
    this->view->info_box.setMoney(money_info->player - 1, money_info->player_money);
    std::cout << "lose money ?" << std::endl;
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
    std::cout << "beforemove2" << std::endl;
    this->view->board.movePlayer(move_card_info->new_pos, move_card_info->player-1);
}

void GameGUIController::moveOnCardCellGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<MoveOnCardCellInfo> move_cardcell_info = game_parser.parseMoveOnCardCellQuery();
    std::cout << "beforemove3" << std::endl;
    this->view->board.movePlayer(move_cardcell_info->new_pos, move_cardcell_info->player - 1 );
    std::cout << "card" << std::endl;
    if (this->model->isMyTurn()){
         std::cout << "card2" << std::endl;
        this->view->message_box.setString("Vous venez de piocher une carte :");
        this->view->card_title.setHidden();
        this->view->dice.setVisible();
        this->view->card_text.setVisible();
         std::cout << "card3" << std::endl;
        this->view->card_text.setString(move_cardcell_info->description);
         std::cout << "card4" << std::endl;
    } 
    else {
        std::cout << "move_cardcell_info->player" << move_cardcell_info->player << std::endl;
         std::cout << "in" << std::endl;
        this->view->message_box.setString(players_username[move_cardcell_info->player - 1] + " pioche un carte.");
        std::cout << "out" << std::endl;
        }
}

void GameGUIController::drawCardGU(const std::string& response){
    this->view->message_box.setString("Vous venez de piocher une carte :" + response);}


void GameGUIController::buildPropertyGU(const std::string& response){
    InGameParser game_parser(response);
    selection_mode = *game_parser.parseSelectPropertyQuery().get();
    std::cout << "build1" << std::endl; 
    if (this->model->isMyTurn()){
        this->view->setSpeRound(true);
        this->view->other_mode = true;
        std::cout << "build2" << std::endl; 
        this->view->board.setAllGrayed();
        std::cout << "build3" << std::endl; 
        for (auto& property : selection_mode){
            std::cout << "build4" << std::endl; 
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
    std::cout << "echange0" << std::endl;
    std::cout << game_info->nb_player << std::endl;
    ExchangeInfo exchanges(response, 0);
    std::cout << "echange" << std::endl;
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
        std::cout << "hypo1" << std::endl;
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
    std::cout << "quitter" << std::endl;
    for (auto& property : selection_mode) {
        int index = this->view->board.getCellIndex(property);
        this->view->board.leaveSelection(index);
    }
    this->view->board.unsetAllGrayed();
}


void GameGUIController::buildOrSellSucceedGU(const std::string& response){
    InGameParser game_parser(response);
    std::shared_ptr<BuildInfo> success_info = game_parser.parseBuildQuery();
    std::cout << "buil reussi" << std::endl;
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
    std::cout << "echange okk" << std::endl;
	int index = this->view->board.getCellIndex(succeed.property);
    if (this->model->isMyTurn()){
        std::cout << "echange okk in" << std::endl;
        this->view->exchange_mode = true;
        this->view->setBoardClickMode(true);
        this->view->board.leaveSelection(index); 
	    this->view->board.setPurchased(index, succeed.player -1);}
}

void GameGUIController::askExchangeGU(const std::string & response){
    std::cout << "echange ?" << std::endl;
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
    std::cout << "ein" << std::endl;
    BetInfo bet(response);
    this->view->message_box.setString("Des encheres pour acheter " + bet.property + " debutent !");
     std::cout << "eout" << std::endl;
}

void GameGUIController::auctionBidGU(const std::string& response){
     std::cout << "ain" << std::endl;
    PlayerBetInfo bet(response);
    if (bet.player != ""){
          std::cout << "ain2" << std::endl;
        this->view->message_box.setString(bet.player + " est sur le point d'acheter le terrain pour : " + std::to_string(bet.amount) + "$");
    }
    else this->view->message_box.setString( "Le prix de depart est : " + std::to_string(bet.amount) + "$ !");
    if (! this->model->isMyTurn()){
          std::cout << "ain3" << std::endl;
        this->view->message_box.setString("valider pour surencherir !");
        this->view->setAuctionRound(true);
        this->view->auction_box.setTextNumber(bet.amount);
        this->view->auction_box.setAuctionLimit(bet.amount);
        }  
        std::cout << "ain4" << std::endl;
}

void GameGUIController::endAuctionGU(const std::string& response){
   EndAuctionInfo end(response);
   std::cout << "ench fin1" << std::endl;
    if (end.player != ""){
        this->view->message_box.setString(end.player + " remporte " + end.property + " pour " + std::to_string(end.amount) + "$ !");
    }
    else this->view->message_box.setString("Personne ne remporte " + end.property + ".");}

void GameGUIController::endGameGU(const std::string& response){
    this->view->message_box.setString("Victoire de " + response + ". Félicitations !");
    this->view->setEnd(true);
    this->view->endTurn();
}

void GameGUIController::wonLandGU(const std::string& response){
    WonLand won_land(response);
    int index = this->view->board.getCellIndex(won_land.land);
    this->view->board.setPurchased(index, won_land.player - 1);
}
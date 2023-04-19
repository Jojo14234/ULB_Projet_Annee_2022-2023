#include "GameServer.hpp"
#include "../../../Game/Board/Obtainable/Cells/LandCell.hpp"
#include "../../ClientManager/ClientManager.hpp"
#include "../../../Utils/Config/Configs.hpp"
#include "../../../Game/Board/Obtainable/Cells/Land/Land.hpp"
#include "../../../Utils/Exceptions.hpp"
#include "string.h"
#include "../Utility/Timer.hpp"
#include "../../../Game/Capitalist.hpp"
#include <string>

#include <stdlib.h>
#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <stdexcept>



// INFOS / MESSAGE

int GameServer::getCurrentPlayerIndex(){
    return this->game.getCurrentPlayer()->getIndex();
}

/*
 * Send Start infos formatted for the n-curse terminal
 */
void GameServer::sendStartData() {
    this->updateAllClientsWithQuery(QUERY::INFOS_START, this->game.getStartInfos());
}

/*
 * Send data formatted for the n-curse terminal
 */
void GameServer::sendGameData() {
    this->updateAllClientsWithQuery(QUERY::INFOS_GAME, this->game.getGameInfos());
    this->updateAllClientsWithQuery(QUERY::INFOS_NEW_TURN, this->game.getCurrentPlayer()->getUsername());
}

/*
 * Show the game infos formatted for better visibility on the terminal
 */
void GameServer::sendBetterGameData() {
    this->updateAllClientsWithQuery(QUERY::USELESS_MESSAGE, this->game.getBetterGameInfos());
}

/*
 * Send a Message with the username and the game code to everyone
 */
void GameServer::clientJoinGameInfos(ClientManager &client) {
    std::string str = client.getUsername() + ":" + std::to_string(this->getCode()) + ":" +
                      std::to_string(game.isFastGame()) + ":" + std::to_string(game.getStartMoney()) + ":" + 
                      std::to_string(game.getMaxPlayers()) + ":" + std::to_string(game.getMaxHome()) + ":" + 
                      std::to_string(game.getMaxHotels()) + ":" + std::to_string(game.getMaxTurns()) + ":" +
                      std::to_string(this->clients.size()) + ":";
    for (size_t i = 0; i < this->clients.size(); i++){
        str += this->clients[i]->getUsername();
        if (i != this->clients.size()-1) str += ":"; 
    }
    this->updateAllClientsWithQuery(QUERY::PLAYER_JOIN_GAME, str);
}

/*
 * Send a message to the player that is in jail
 */
void GameServer::playerInJailInfos(ClientManager &client) {
    Player* me = findMe(client);
    this->updateThisClientWithQuery(QUERY::INFOS_NEW_TURN_IN_JAIL, std::to_string(me->getRollsInPrison()) + ":" + std::to_string(me->getAllGOOJCards().size() > 0), client);
}

/*
 * Send a message to the that want to build
 */
void GameServer::playerBuildInfos(ClientManager &client) {
    Player* me = findMe(client);
    this->updateThisClientWithQuery(QUERY::INFOS_BUILD_PROP, me->getAllBuildableProperties(game.isFastGame()), client);
}

void GameServer::playerSellBuildInfos(ClientManager &client) {
    Player* me = findMe(client);
    this->updateThisClientWithQuery(QUERY::INFOS_SELL_BUILD, me->getAllSellableBuildProperties(), client);
}

void GameServer::playerMortgageInfos(ClientManager &client) {
    Player* me = findMe(client);
    this->updateThisClientWithQuery(QUERY::INFOS_MORTGAGEABLE_PROP, me->getAllPossessionMortgageable(), client);
}

void GameServer::playerLiftMortgageInfos(ClientManager &client) {
    Player* me = findMe(client);
    this->updateThisClientWithQuery(QUERY::INFOS_LIFT_MORTGAGEABLE_PROP, me->getAllPossessionLiftMortgageable(), client);   
}

void GameServer::playerExchangeInfos(ClientManager &client) {
    std::string str = "";
    for ( auto &player : *this->game.getPlayers() ) {
        if ( player.getClient() == &client ) { continue; }
        str += std::to_string(player.getIndex()) + "=" + player.getAllExchangeablePossession() + "|";
    }
    this->updateThisClientWithQuery(QUERY::INFOS_EXCHANGEABLE_PROP, str, client);
}

void GameServer::playerDebtInfos(ClientManager &client, Player* player) {
    std::string str = "";
    str += std::to_string(player->getDebt() - player->getMoney());
    str += ":";
    if (player->isBankruptToPlayer()) {str += player->getPlayerToRefund()->getUsername();}
    else { str += "BANK"; }
    this->updateThisClientWithQuery(QUERY::INFOS_DEBT, str, client);
}


// GESTION CLIENT

/*
 * Permet de connecter le client à la partie
 *
 * Add client to Clients list
 * Add This server tho client.gameServer
 * Create and Add a Player to the game (this player is link to the client)
 * Set the index of this player
 */
void GameServer::connectClientToThisGame(ClientManager &client) {
    this->clients.push_back(&client);
    client.setGameServer(this);
    this->addPlayer(client);
    //this->clientJoinGameInfos(client); // todo c'est ça qui envoie 2 fois Bao
}

/*
 * Remove a client form the Clients list
 */
void GameServer::removeClient(ClientManager* client) {
    unsigned int i = 0;
    this->game.removePlayer(*client);
    while ( i < this->clients.size() ) {
        if (this->clients[i] == client) {
            this->clients[i]->setGameServer(nullptr);
            this->clients[i] = this->clients[this->clients.size()-1];
            this->clients.pop_back();
            break;
        }
        i++;
    }
}

/*
 * Create and Add a player to the game
 * The player is link to the client (but the client is not link to the player)
 * Set the index of the player (it's like an Id that will never change during the game)
 */
void GameServer::addPlayer(ClientManager &client) {
    this->game.addPlayer(client);
    int new_index = game.getPlayersSize() - 1;
    this->game.getPlayers()->at(new_index).setIndex(new_index);
}



// UTILITAIRE

/*
 * Return the player link to the clientManager
 */
Player *GameServer::findMe(ClientManager &client) {
    unsigned int i = 0;
    while (i < this->game.getPlayers()->size()) {
        if ( this->game.getPlayers()->operator[](i).isItMe(client) ) { return &this->game.getPlayers()->operator[](i); }
        i++;
    }
    return nullptr;
}

Land *GameServer::getLand(std::string &name) {
    LandCell* land_cell = game.getLandCell(name);
    if (land_cell == nullptr){
        return nullptr;
    }
    Land* land = land_cell->getLand();
    return land;
}

/*
 * Renvoie une GAME_QUERY obtenue depuis un client.receive().
 */
GAME_QUERY_TYPE GameServer::getGameQuery(ClientManager &client) {
    GAME_QUERY_TYPE query;
    client.receive(query);
    return query;
}



// LOOP
/*
 * Loop for the client when he join the gameServer
 */
GameStats GameServer::clientLoop(ClientManager &client) {
    Player* me = this->findMe(client);
    this->clientJoinGameInfos(client);

    // LOOP UNTIL THE HOST START THE GAME
    while ( !this->game.isRunning() ) {
        // ACTION POSSIBLE IF YOU ARE THE HOST
        if ( me->isAdmin() ) {
            this->processStart(&client);
            // TODO
        }
        // ACTION POSSIBLE IF YOU ARE NOT THE HOST
        else {
            // TODO
            sleep(1); // fait moins lag
        }
    }

    // LOOP UNTIL THERE IS A WINNER
    while ( this->game.getWinner() == nullptr ) {

        // POSSIBLE ACTION IF IT IS THE CLIENT TURN
        if (this->game.getCurrentPlayer()->getClient() == &client) {
            Player* me = this->game.getCurrentPlayer();

            if ( me->getStatus() == PLAYER_STATUS::FREE ) { this->clientTurn(client, me); continue; }
            if ( me->getStatus() == PLAYER_STATUS::JAILED ) { this->processJail(client, me); continue; }
            if ( me->getStatus() == PLAYER_STATUS::LOST ) { this->processLost(client); continue; }
        }
        // POSSIBLE ACTION ITS NOT THE CLIENT TURN
        else {
            Player* me = this->findMe(client);
            if ( !me ) { sleep(5); continue; }
            if ( me->getStatus() == PLAYER_STATUS::IN_EXCHANGE ) { this->processAskExchange(client, me); }
            if ( me->getStatus() == PLAYER_STATUS::WAITING_FOR_AUCTION_TURN ) { /*Il n'y a rien à faire à part attendre*/ }
            if ( me->getStatus() == PLAYER_STATUS::AUCTION_TURN ) { this->processAskBid(client, me); continue;}
            /*
             * TODO : LeaveGame
             */

            sleep(1); // fait moins lag
        }
    }
    // STOP THE GAME
    this->game.setRunning(false);
    // allow client to get out of the receiveFromServerLoop and SendToServerLoop
    updateThisClientWithQuery(QUERY::WIN, this->game.getWinner()->getUsername(), client);
    updateThisClientWithQuery(QUERY::ENDGAME, "", client);

    // RETURN STATS for winner and looser.
    if ( this->game.getWinner() == &client ) { return GameStats{(int)this->clients.size(), 1, 1}; }
    else { return GameStats{client.getScore(), 1, 0}; }
}

/*
 * Gestion des action possible durant le tour du client
 */
void GameServer::clientTurn(ClientManager &client, Player* me) {

    while ( !me->hasRolled() and me->getStatus() != PLAYER_STATUS::LOST) {
        GAME_QUERY_TYPE query = this->getGameQuery(client);
        if ( query == GAME_QUERY_TYPE::BUILD )          { this->processBuild(client, me); continue; }
        if ( query == GAME_QUERY_TYPE::SELL_BUILDINGS ) { this->processSellBuild(client, me); continue; }
        if ( query == GAME_QUERY_TYPE::MORTGAGE )       { this->processMortgage(client, me); continue; }
        if ( query == GAME_QUERY_TYPE::LIFT_MORTGAGE )  { this->processLiftMortgage(client, me); continue; }
        if ( query == GAME_QUERY_TYPE::EXCHANGE )       { this->processExchange(client, me); continue; }


        if ( query == GAME_QUERY_TYPE::ROLL_DICE ) {
            // Lancement de dés + dép + action_cell
            this->processRollDice(client, me);

            // Lancement enchère si c'est une case achetable + si personne ne la possède
            LandCell* landCell = dynamic_cast<LandCell*>(me->getCurrentCell());
            if ( landCell && !landCell->getLand()->getOwner() ) { this->processAuction(me, landCell->getLand()); }

            // Vérification si le joueur est en faillite

            checkAndManageBankruptcy(client, me);
        }
    }
    // End of the turn
    this->game.getDice().resetDoubleCounter();
    if ( game.isFastGame() ){
        me->pay(20, true);
        checkAndManageBankruptcy(client, me);
    }
    this->game.endCurrentTurn();
    this->sendGameData();
    this->sendBetterGameData();

}

void GameServer::checkAndManageBankruptcy(ClientManager &client, Player* me){
    if ( me->getStatus() == PLAYER_STATUS::BANKRUPT_SUSPECTED ) { this->suspectBankrupt(me); }
    if ( me->getStatus() == PLAYER_STATUS::DEBT ) { this->processPayDebt(client, me); }
    if ( me->getStatus() == PLAYER_STATUS::BANKRUPT_CONFIRMED ) { this->processBankrupt(client, me); }
    if ( me->getStatus() == PLAYER_STATUS::LOST ) { this->processLost(client); }
}


// PROCESS

/*
 * Lance la partie si il y a au moins 2 joueurs
 */
void GameServer::processStart(ClientManager* client) {
    if ( this->game.isRunning() ) { return; }
    GAME_QUERY_TYPE query;
    client->receive(query);
    if ( query != GAME_QUERY_TYPE::START ) { this->updateThisClientWithQuery(QUERY::INFOS_NOT_STARTED, "" ,*client); return; }
    if ( this->game.getPlayersSize() < 2 ) { this->updateThisClientWithQuery(QUERY::INFOS_CANNOT_START, "" ,*client); return; }
    this->game.startGame();

    if ( game.isFastGame() ){
        for (auto p : *(this->game.getPlayers())){
            game.forceAcquisition(&p);
            checkAndManageBankruptcy(*p.getClient(), &p);
        }
    }
    this->sendStartData();
}

/*
 * Roll the dice,
 * check if that's the third time you do a double ans end you in jail if it's the case
 * move the player to the right case
 * Do the action cell
 */
void GameServer::processRollDice(ClientManager &, Player *player) {
    int roll_result = player->processRollDice(this->game.getDice());

    // Update the other player of the game
    this->updateAllClientsWithQuery(QUERY::INFOS_ROLL_DICE, player->rollInfos(this->game.getDice()));


    // SI on a fait 3 double notre status est passé à JAILED;
    if ( player->getStatus() == PLAYER_STATUS::JAILED ) { 
        player->processMove(this->game.getBoard()[10], false);
        player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_SEND_TO_PRISON, player->getUsername());
        return;
    }

    // Déplacement du joueur
    Cell* new_cell = player->processMove(roll_result, this->game.getBoard());

    // Action de la case
    new_cell->action(player);
}

//a
void GameServer::processJail(ClientManager &client, Player *player) {
    // Informer de ses droit :
    // - Soit lancer les dés et faire un double
    // - Soit utiliser une carte sortie de prison / lancer les dés
    // - Payer 50$ + lancer les dés
    // CONDITION : 3 tours max
    // TODO tester la /use
    this->playerInJailInfos(client);
    GAME_QUERY_TYPE query;
    bool is_valid=false;
    while (! is_valid){
        client.receive(query);
        switch (query) {
            case GAME_QUERY_TYPE::PAY : { 
                if (this->game.processJailPay(player)) {is_valid=true;} 
                else client.sendQueryMsg("", QUERY::INFOS_NOT_ENOUGH_MONEY);
                break;
            }
            case GAME_QUERY_TYPE::USEGOOJCARD : {
                if (this->game.processJailUseCard(player)) {is_valid=true;}
                else client.sendQueryMsg("", QUERY::BAD_COMMAND);
                break;
            }
            case GAME_QUERY_TYPE::ROLL_DICE :   if (this->game.processJailRoll(player)) is_valid=true; break;
            default: client.sendQueryMsg("", QUERY::BAD_COMMAND); break;
        }
    }
    // End of the turn
    if ( player->getStatus() != PLAYER_STATUS::BANKRUPT_SUSPECTED ) {
        if (this->game.isFastGame()) player->getBankAccount()->pay(20);
        this->game.endCurrentTurn();
        this->sendGameData();
        this->sendBetterGameData();
    }

}

void GameServer::processBuild(ClientManager &client, Player *player) {
    // Afficher les propriété constructible
    // JOUEUR choisis une propriété / ou leave
    // Vérifier si il a assez de thune
    // Ajouter un niveau à la propriété

    if (! player->hasBuildableProperties()) {
        this->updateThisClientWithQuery(QUERY::NO_BUILDABLE_PROP, "", client);
        return;
    }
    this->playerBuildInfos(client);

    GAME_QUERY_TYPE query;
    std::string property_name;
    sf::Packet packet;
    client.receive(query, packet);

    while ( query != GAME_QUERY_TYPE::LEAVE_SELECTION ) {
        // QUERY IS NOT SELECT -> SHOW MESSAGE AND ASK FOR ANOTHER INPUT
        if ( query != GAME_QUERY_TYPE::SELECT ) {
            this->updateThisClientWithQuery(QUERY::BAD_COMMAND, "", client);
            client.receive(query, packet);
            continue;
        }
        // QUERY IS SELECT
        packet >> property_name;
        // BUILDING PROCESS WORK
        if ( this->game.processBuild(player, property_name) ) {
            Property* prop = dynamic_cast<Property*>(this->game.getLandCell(property_name)->getLand());
            this->updateAllClientsWithQuery(QUERY::INFOS_BUILD_SUCCESS, property_name + ":" + std::to_string(prop->getIntLevel()) + ":" + std::to_string(prop->isMortgaged()));
        }
        // BUILDING PROCESS DIDN'T WORK
        else this->updateThisClientWithQuery(QUERY::CANNOT_BUILD, "", client);
        client.receive(query, packet);
    }
    this->updateThisClientWithQuery(QUERY::INFOS_LEAVE_SELECTION_MODE, "", client);
}

void GameServer::processSellBuild(ClientManager &client, Player *player) {
    // récupérer toute les propriétés en état de perdre une maison
    if (! player->hasSellableProperties()) {
        this->updateThisClientWithQuery(QUERY::NO_SALABLE_PROP, "", client);
        return;
    }
    this->playerSellBuildInfos(client);

    GAME_QUERY_TYPE query;
    std::string property_name;
    sf::Packet packet;
    client.receive(query, packet);

    while ( query != GAME_QUERY_TYPE::LEAVE_SELECTION ) {
        if ( query != GAME_QUERY_TYPE::SELECT ) {
            this->updateThisClientWithQuery(QUERY::BAD_COMMAND, "", client);
            client.receive(query, packet);
            continue;
        }
        // QUERY IS SELECT
        packet >> property_name;
        // BUILDING PROCESS WORK
        if ( this->game.processSellBuild(player, property_name) ) {
            Property* prop = dynamic_cast<Property*>(this->game.getLandCell(property_name)->getLand());
            this->updateAllClientsWithQuery(QUERY::INFOS_SELL_BUILD_SUCCESS, property_name + ":" + std::to_string(prop->getIntLevel()) + ":" + std::to_string(prop->isMortgaged()));
        }

        // SELL PROCESS DIDN'T WORK
        else this->updateThisClientWithQuery(QUERY::CANNOT_SELL, "", client);
        client.receive(query, packet);
    }
    this->updateThisClientWithQuery(QUERY::INFOS_LEAVE_SELECTION_MODE, "", client);

}

void GameServer::processMortgage(ClientManager &client, Player *player) {
    // montrer toutes les propriété hypothécable du joueur
    // Choisir cell a hypothéquer / quitter le menu
    // passer la case en hypothèque + recevoir / prix achat
    if (! player->hasMortgageableLand()) {
        this->updateThisClientWithQuery(QUERY::NO_MORTGAGEABLE_PROP, "", client);
        return;
    }
    this->playerMortgageInfos(client);

    GAME_QUERY_TYPE query;
    std::string property_name;
    sf::Packet packet;
    client.receive(query, packet);

    while ( query != GAME_QUERY_TYPE::LEAVE_SELECTION ) {
        // QUERY IS NOT SELECT -> SHOW MESSAGE AND ASK FOR ANOTHER INPUT
        if ( query != GAME_QUERY_TYPE::SELECT ) {
            this->updateThisClientWithQuery(QUERY::BAD_COMMAND, "", client);
            client.receive(query, packet);
            continue;
        }
        // QUERY IS SELECT
        packet >> property_name;
        // BUILDING PROCESS WORK
        if ( this->game.processMortgage(player, property_name, game.isFastGame()) ) {
            this->updateAllClientsWithQuery(QUERY::INFOS_MORTGAGE_SUCCESS, property_name + ":0:1");
        }

        // SELL PROCESS DIDN'T WORK
        else this->updateThisClientWithQuery(QUERY::CANNOT_MORTAGE, "", client);
        client.receive(query, packet);
    }
    this->updateThisClientWithQuery(QUERY::INFOS_LEAVE_SELECTION_MODE, "", client);
}

void GameServer::processLiftMortgage(ClientManager &client, Player *player) {
    // montrer toutes les propriété des-hypothécable du joueur
    // Choisir cell a des-hypothéquer / quitter le menu
    // passer la case en normale + perdre / prix de rachat
    if (! player->hasUnmortgageableLand()) {
        this->updateThisClientWithQuery(QUERY::NO_UNMORTGAGEABLE_PROP, "", client);
        return;
    }
    this->playerLiftMortgageInfos(client);

    GAME_QUERY_TYPE query;
    std::string property_name;
    sf::Packet packet;
    client.receive(query, packet);

    while ( query != GAME_QUERY_TYPE::LEAVE_SELECTION ) {
        // QUERY IS NOT SELECT -> SHOW MESSAGE AND ASK FOR ANOTHER INPUT
        if ( query != GAME_QUERY_TYPE::SELECT ) {
            this->updateThisClientWithQuery(QUERY::BAD_COMMAND, "", client);
            client.receive(query, packet);
            continue;
        }
        // QUERY IS SELECT
        packet >> property_name;
        // BUILDING PROCESS WORK
        if ( this->game.processLiftMortgage(player, property_name, game.isFastGame()) ) {
            this->updateAllClientsWithQuery(QUERY::INFOS_LIFT_MORTGAGE_SUCCESS, property_name + ":0:0");
        }

        // SELL PROCESS DIDN'T WORK
        else this->updateThisClientWithQuery(QUERY::CANNOT_UNMORTGAGE, "", client);
        client.receive(query, packet);
    }
    this->updateThisClientWithQuery(QUERY::INFOS_LEAVE_SELECTION_MODE, "", client);
}

void GameServer::processExchange(ClientManager &client, Player *player) {
    // Récupérer toutes les cases échangeable d'une partie
    // Une case échangeable = une case qui n'a pas de bâtiment
    if (! player->canExchangeLand()) {
        this->updateThisClientWithQuery(QUERY::NO_EXCHANGEABLE_PROP, "", client);
        return;
    }
    this->playerExchangeInfos(client);

    GAME_QUERY_TYPE query;
    std::string property_name;
    std::string money_s;
    sf::Packet packet;
    client.receive(query, packet);

    while ( query != GAME_QUERY_TYPE::LEAVE_SELECTION ) {
        // QUERY IS NOT SELECT -> SHOW MESSAGE AND ASK FOR ANOTHER INPUT–
        if ( query != GAME_QUERY_TYPE::TRADE ) {
            this->updateThisClientWithQuery(QUERY::BAD_COMMAND, "", client);
            client.receive(query, packet);
            continue;
        }
        // QUERY IS SELECT
        packet >> property_name >> money_s;
        int money = std::atoi(money_s.c_str());

        // BUILDING PROCESS WORK
        ExchangeResult result = this->game.processSendExchangeRequest(player, property_name, money);
        if ( result == ExchangeResult::ACCEPTED ) {
            this->updateAllClientsWithQuery(QUERY::INFOS_EXCHANGE_SUCCESS, property_name + ":" + std::to_string(player->getIndex()));
        }
        else if ( result == ExchangeResult::REFUSED) {
            this->updateThisClientWithQuery(QUERY::EXCHANGE_REFUSED, "", client);
        }

        // SELL PROCESS DIDN'T WORK
        else this->updateThisClientWithQuery(QUERY::CANNOT_EXCHANGE, "", client);
        client.receive(query, packet);
    }
    this->updateThisClientWithQuery(QUERY::INFOS_LEAVE_SELECTION_MODE, "", client);
}

void GameServer::processAskExchange(ClientManager &client, Player *player) {
    sleep(MAX_WAIT_EXCHANGE);
    if (player->getStatus() == PLAYER_STATUS::IN_EXCHANGE) {
        this->updateThisClientWithQuery(QUERY::STOP_WAIT, "/refuse", client);
        player->setStatus(PLAYER_STATUS::FREE);
    }
}

void GameServer::processAskBid(ClientManager &client, Player *player) {
    //std::cout << "tic tac toe " << std::endl;
    player->setStatus(PLAYER_STATUS::OTHER);
    sleep(MAX_WAIT_EXCHANGE);
    if (player->getStatus() == PLAYER_STATUS::OTHER) {
        this->updateThisClientWithQuery(QUERY::STOP_WAIT, "/out", client);
    }
}

void GameServer::processAuction(Player *me, Land* land) {
    // Passer tout les joueurs autre que me en status in_auction
    // récupérer un /participate et les ajouter à un vecteur
    // boucler un a un sur leur offres
    std::string name = land->getName();
    int starting_bid = land->getPurchasePrice();
    std::vector<Player*> participants = this->game.startAuction(me);
    this->updateAllClientsWithQuery(QUERY::INFOS_AUCTION_START, land->getName()+":"+std::to_string(land->getPurchasePrice()));
    
    // AUCTION
    Player* futur_owner = nullptr;
    while ( true ) {

        for ( auto& player : participants ) {
            if (player->getStatus() != PLAYER_STATUS::WAITING_FOR_AUCTION_TURN || player == futur_owner) { continue; }
            player->setStatus(PLAYER_STATUS::AUCTION_TURN);

            player->getClient()->sendQueryMsg(":"+std::to_string(starting_bid), QUERY::INFOS_AUCTION_BID);

            GAME_QUERY_TYPE query;
            sf::Packet packet;
            std::string bid_s;
            int bid;

            player->getClient()->receive(query, packet); //player's answer
            // PLAYER'S ANSWER VERIFICATION
            if (query == GAME_QUERY_TYPE::LEAVE_BID) { 
                player->getClient()->sendQueryMsg("", QUERY::LEAVE_BID); 
                player->setStatus(PLAYER_STATUS::FREE); continue; 
            }
            else if ( query != GAME_QUERY_TYPE::BID ) { 
                player->getClient()->sendQueryMsg("", QUERY::BAD_COMMAND); 
                player->setStatus(PLAYER_STATUS::WAITING_FOR_AUCTION_TURN);
                player->getClient()->sendQueryMsg("", QUERY::WAIT_YOUR_TURN);
                  continue; 
            }
            packet >> bid_s;
            try { bid = std::stoi(bid_s); }
            catch ( ... ) { 
                player->getClient()->sendQueryMsg("", QUERY::BAD_AMOUNT);
                player->setStatus(PLAYER_STATUS::WAITING_FOR_AUCTION_TURN);
                player->getClient()->sendQueryMsg("", QUERY::WAIT_YOUR_TURN);  continue; }


            // Vérifier que player possède assez de thune
            if ( player->getBankAccount()->getMoney() < bid ) { 
                player->setStatus(PLAYER_STATUS::FREE); 
                player->getClient()->sendQueryMsg("", QUERY::NOT_ENOUGH_MONEY_TO_PARTICIPATE); continue; 
            }
            // Vérifier prix > starting bid
            if ( bid <= starting_bid ) { 
                player->getClient()->sendQueryMsg("", QUERY::BAD_AMOUNT);
                player->getClient()->sendQueryMsg("", QUERY::WAIT_YOUR_TURN); 
                player->setStatus(PLAYER_STATUS::WAITING_FOR_AUCTION_TURN); continue; 
            }

            this->updateAllClientsWithQuery(QUERY::INFOS_AUCTION_BID, player->getUsername() + ":" + bid_s);
            // starting bid = nouveau prix // futur owner = player
            starting_bid = bid;
            futur_owner = player;

            player->setStatus(PLAYER_STATUS::WAITING_FOR_AUCTION_TURN);
            player->getClient()->sendQueryMsg("", QUERY::WAIT_YOUR_TURN); 
        }
        int count = 0;
        for ( auto& player : participants ) {
            if (player->getStatus() == PLAYER_STATUS::WAITING_FOR_AUCTION_TURN ) {count++;}
        }
        if (count <= 1) { break; }
    }
    std::string res = futur_owner ? futur_owner->getUsername() + ":" + land->getName()+ ":" + std::to_string(starting_bid)
                      : ":" + land->getName()+ ":" + std::to_string(starting_bid);
    this->updateAllClientsWithQuery(QUERY::INFOS_AUCTION_END, res);
    for ( auto& player : participants ) { player->setStatus(PLAYER_STATUS::FREE); } // security
    // Si futur_owner != nullptr -> futur->owner.acquire.prop
    if (futur_owner) {
        futur_owner->setStatus(PLAYER_STATUS::FREE);
        futur_owner->acquireLand(land);
        futur_owner->pay(starting_bid);
    }
}

void GameServer::processPayDebt(ClientManager &client, Player *player) {
    while ( player->isBankrupt() ) {
        this->playerDebtInfos(client, player);
        GAME_QUERY_TYPE query = this->getGameQuery(client);
        this->game.getBetterGameInfos();
        if ( query == GAME_QUERY_TYPE::SELL_BUILDINGS ) { this->processSellBuild(client, player); continue; }
        if ( query == GAME_QUERY_TYPE::MORTGAGE )       { this->processMortgage(client, player); continue; }
    }

    if ( player->isBankruptToPlayer() ) {
        player->getPlayerToRefund()->receive(player->getDebt());
    }
    player->pay(player->getDebt(), true);
    player->resetDebt();
}


/*--------------------------------------------------------------------------------------------------------------------*/

void GameServer::suspectBankrupt(Player *player) {
    if (this->game.checkBankrupt(player)) { player->setStatus(PLAYER_STATUS::BANKRUPT_CONFIRMED); }
    else { player->setStatus(PLAYER_STATUS::DEBT); }
}


void GameServer::processBankruptByGame(Player *player) {
    for ( auto property : player->getAllProperties() ) {
        property->reset();
        this->processAuction(player, property);
    }
    for ( auto station : player->getAllStations() ) {
        station->reset();
        this->processAuction(player, station);
    }
    for ( auto company : player->getAllCompanies() ) {
        company->reset();
        this->processAuction(player, company);
    }
}

void GameServer::processBankruptByPlayer(ClientManager &client, Player *player, Player *other) {
    this->updateThisClientWithQuery(QUERY::MESSAGE, "Vous venez de faire faillite, vous donnez toutes vos possessions au joueur ayant provoqué votre faillite.", client);
    this->game.processBankruptByPlayer(player, other);
}

void GameServer::processBankrupt(ClientManager &client, Player *player) {
    if ( player->isBankruptToPlayer() ) { this->processBankruptByPlayer(client, player, player->getPlayerToRefund()); }
    else {this->processBankruptByGame(player); }
    player->setStatus(PLAYER_STATUS::LOST);
}

void GameServer::processLost(ClientManager &client) {
    client.setScore(this->clients.size() - this->game.getPlayersSize() + 1);
    this->game.removePlayer(client);
}


/*--------------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/


void GameServer::updateAllClients(std::string update) {
    for ( auto client : clients ) {
        client->send(update);
    }
}

void GameServer::updateAllClientsWithQuery(QUERY &&query, std::string update) {
    for ( auto client : clients ) {
        client->sendQueryMsg(update, query);
    }
}

void GameServer::updateThisClientWithQuery(QUERY &&query, std::string update, ClientManager &client) {
    client.sendQueryMsg(update, query);
}

/*--------------------------------------------------------------------------------------------------------------------*/


int GameServer::getCode() const { return code.getCode(); }

Capitalist* GameServer::getGame() {
    return &game;
}

bool GameServer::isCode(int other) const { return code.getCode() == other; }

CardDeck* GameServer::getDeck(std::string name){
    return this->game.getBoard().getDeck(name).get();
}

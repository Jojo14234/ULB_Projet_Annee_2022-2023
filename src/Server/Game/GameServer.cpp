#include "GameServer.hpp"
#include "../../Game/Board/Obtainable/Cells/LandCell.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"
#include "../../Game/Board/Obtainable/Cells/Land/Land.hpp"
#include "string.h"
#include "Timer.hpp"
#include "../../Game/Capitalist.hpp"
#include <string>
#include "../../utils/Configs.hpp"

#include <stdlib.h>
#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <stdexcept>



// INFOS / MESSAGE

/*
 * Send Start infos formatted for the n-curse terminal
 */
void GameServer::sendStartData() {
    this->updateAllClientsWithQuery(QUERY::MESSAGE, this->game.getStartInfos());
}

/*
 * Send data formatted for the n-curse terminal
 */
void GameServer::sendGameData() {
    this->updateAllClientsWithQuery(QUERY::INFOS_GAME, this->game.getGameInfos());
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
void GameServer::client_has_join_the_game(ClientManager &client) {
    std::string name = client.getUsername();
    std::string gc = std::to_string(this->getCode());
    this->updateAllClientsWithQuery(QUERY::PLAYER_JOIN_GAME, name + ":" + gc);
}

/*
 * Send a message with the new player and the size of the clients connected to this game
 */
void GameServer::clientsSizeData(ClientManager &client) {
    std::string username = client.getUsername();
    std::string clientsSize = std::to_string(this->clients.size());
    std::string str = username + " enter the game !\n";
    str += "Your are now [" + clientsSize + "] in this game.";
    this->updateAllClientsWithQuery(QUERY::MESSAGE, str);
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
    this->client_has_join_the_game(client);
}

/*
 * Remove a client form the Clients list
 */
void GameServer::removeClient(ClientManager* client) {
    int i = 0;
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





// UTILITAIRE

/*
 * Return the player link to the clientManager
 */
Player *GameServer::findMe(ClientManager &client) {
    int i = 0;
    while (i < this->game.getPlayers()->size()) {
        if ( this->game.getPlayers()->operator[](i).isItMe(client) ) { return &this->game.getPlayers()->operator[](i); }
        i++;
    }
    return nullptr;
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
int GameServer::clientLoop(ClientManager &client) {
    Player* me = this->findMe(client);
    this->clientsSizeData(client); // MESSAGE

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
        }
    }

    // LOOP UNTIL THERE IS A WINNER
    while ( this->game.getWinner() == nullptr ) {

        // POSSIBLE ACTION IF IT IS THE CLIENT TURN
        if (this->game.getCurrentPlayer()->getClient() == &client) {
            Player* me = this->game.getCurrentPlayer();

            if ( me->getStatus() == PLAYER_STATUS::FREE ) { this->clientTurn(client, me); continue; }
            if ( me->getStatus() == PLAYER_STATUS::LOST ) { /*TODO manage lost*/; me->getClient()->setRankForActualGame(this->game.getPlayersSize()+1); continue; }
            if ( me->getStatus() == PLAYER_STATUS::JAILED ) { /*TODO manage Jail*/; continue; }
            if ( me->getStatus() == PLAYER_STATUS::BANKRUPT ) { /*TODO manage bankrupt*/; continue; }
        }
        // POSSIBLE ACTION ITS NOT THE CLIENT TURN
        else {
            /*
             * TODO : Participate in auction
             * TODO : Exchange
             * TODO : LeaveGame
             */
            continue;
        }
    }
    // SET RANK FOR WINNER
    if ( this->game.getWinner() == me->getClient() ) { client.setRankForActualGame(1); }
    // RETURN RANK
    return client.getRankForActualGame();
}


// PROCESS

/*
 * Roll the dice,
 * check if that's the third time you do a double ans end you in jail if it's the case
 * move the player to the right case
 * Do the action cell
 */
void GameServer::processRollDice(ClientManager &, Player *player) {
    int roll_result = player->processRollDice(this->game.getDice());

    // SI on a fait 3 double notre status est passé à JAILED;
    if ( player->getStatus() == PLAYER_STATUS::JAILED ) { player->processMove(this->game.getBoard()[10], false); return; }

    // Déplacement du joueur
    Cell* new_cell = player->processMove(roll_result, this->game.getBoard());

    // Update the other player of the game
    this->updateAllClientsWithQuery(QUERY::INFOS_ROLL_DICE, player->rollInfos(this->game.getDice()));

    // Action de la case
    new_cell->action(player);
}


/*
 * Lance la partie si il y a au moins 2 joueurs
 */
void GameServer::processStart(ClientManager* client) {
    GAME_QUERY_TYPE query;
    client->receive(query);
    if ( query != GAME_QUERY_TYPE::START ) { this->updateThisClientWithQuery(QUERY::MESSAGE,"Pour démarrer la partie ( /start )" ,*client); return; }
    if ( this->game.getPlayersSize() < 2 ) { this->updateThisClientWithQuery(QUERY::MESSAGE,"Attend tes amis avant de lancer la partie !" ,*client); return; }
    this->game.startGame();
    this->sendStartData();
    this->updateAllClientsWithQuery(QUERY::MESSAGE, "Lancement de la partie");
}

/*--------------------------------------------------------------------------------------------------------------------*/




// GETTER

void GameServer::processBuild(ClientManager &client, Player *player) {
    //TODO
}

void GameServer::processAuction(ClientManager &client, Player *player) {
    //TODO
}

void GameServer::processBankrupt(ClientManager &client, Player *player) {
    //TODO
}

void GameServer::processDiceRoll(ClientManager &client) {
    //TODO
}


void GameServer::clientTurn(ClientManager &client, Player* me) {
    while ( !me->hasRolled() ) {
        GAME_QUERY_TYPE query = this->getGameQuery(client);
        if ( query == GAME_QUERY_TYPE::BUILD )          { this->processBuild(client, me); continue; }
        if ( query == GAME_QUERY_TYPE::SELL_BUILDINGS ) { continue; }
        if ( query == GAME_QUERY_TYPE::MORTGAGE )       { continue; }
        if ( query == GAME_QUERY_TYPE::DEMORTGAGE )     { continue; }
        if ( query == GAME_QUERY_TYPE::EXCHANGE )       { continue; }




        if ( query == GAME_QUERY_TYPE::ROLL_DICE ) {
            // Lancement de dés + dép + action_cell
            this->processRollDice(client, me);

            // Lancement enchère si c'est une case achetable + si personne ne la possède
            LandCell* landCell = dynamic_cast<LandCell*>(me->getCurrentCell());
            if ( landCell && !landCell->getLand()->getOwner() ) { this->processAuction(client, me); }

            // Vérification si le joueur est en faillite
            if ( me->getStatus() == PLAYER_STATUS::BANKRUPT ) { this->processBankrupt(client, me); }
        }
    }
    // End of the turn
    this->game.endCurrentTurn();
    this->sendGameData();
    this->sendBetterGameData();
}

/*
 *     // Message terminal
    str = "\n" + client.getAccount()->getUsername() + " a jeté les dés et obtenu un [" + std::to_string(game.getDice().getDice1()) + " et un " + std::to_string(game.getDice().getDice2()) + "]. Iel avance donc de " + std::to_string(game.getDice().getResults()) + ".";
    str += "\nIel est arrivé sur la case [" + std::to_string(new_cell_idx) + "].";
    str += (game.rolledADouble()) ? "\nC'est un double ! Iel pourra rejouer !\n" : "\n";
    QUERY query = ( game.rolledADouble() ) ? QUERY::ROLL_DICE_DOUBLE : QUERY::ROLL_DICE;
    this->updateAllClientsWithQuery(query, std::to_string(game.getDice().getDice1()) + ":" + std::to_string(game.getDice().getDice2()));
 */


/*
 * Boucle dans laquelle un client est envoyé
 */
void GameServer::clientBeforeRollLoop(ClientManager &client) {
    while ( true ) {
        // Récupération de la query et du player actuel
        GAME_QUERY_TYPE query = this->getGameQuery(client);
        Player* current = this->game.getCurrentPlayer();

        // Si la commande est /start
        if ( query == GAME_QUERY_TYPE::START ) { this->processStart(&client); continue; }

        // Si la partie n'est pas encore lancée
        if ( !this->game.isRunning() ) {
            this->updateThisClientWithQuery(QUERY::NOT_STARTED_GAME, "La partie n'est pas encore lancée.", client);
            //client.send("La partie n'est pas encore lancée.");
            continue;}

        // Si le [client doit jouer] OU qu'il y a une [enchère] OU qu'il y a un [échange]
        if ( current->getClient() == &client or this->game.getAuctionStatus() == AuctionStatus::START or this->game.getExchangeStatus() == ExchangeStatus::START) {

            // ProcessBeforeRoll
            this->processGameQueryBeforeRoll(client, query);

            // Si le joueur a [lancé les dés] ET qu'il n'est pas en status [!perdu]
            if ( game.getCurrentPlayer()->getClient() == &client and current->hasRolled() and current->getStatus() != PLAYER_STATUS::LOST ) {
                this->updateThisClientWithQuery(QUERY::NO_MORE_COMMAND, "Plus de command disponible. Tour automatiquement terminé.", client);
                //client.send("Plus aucune commande ne vous est disponible ce tour ci. Votre tour s'est donc automatiquement terminé.");
                processEndTurn(client);
                break;
            }
            // Si le joueur est en status [perdu]
            if ( current->getStatus() == PLAYER_STATUS::LOST ) {
                updateThisClientWithQuery(QUERY::LOST, "Vous avez perdu !", client);
                //client.send("Vous avez perdu :(");
                break;
            }
        }
        else if ( game.getAuctionStatus() == AuctionStatus::OTHER ) {
            updateThisClientWithQuery(QUERY::NOT_PARTICIPATE_IN_AUCTION, "Une enchère est en cours et vous n'y participez pas !", client);
            //client.send("Une enchère est en cours à laquelle vous ne participez pas. Attendez la fin de l'enchère avant d'entrer d'autres commandes.");
        }
        else {
            updateThisClientWithQuery(QUERY::NOT_MY_TURN, "Ce n'est pas a votre tour de jouer !.", client);
            //client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour.");
        }
    }
}


/*
 * Process une Game_Query
 */
void GameServer::processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query) {
    if (game.getAuctionStatus() == AuctionStatus::STOP) {
        switch (query) {
            case GAME_QUERY_TYPE::END_TURN       : processEndTurn(client); break;
            case GAME_QUERY_TYPE::ROLL_DICE      : processDiceRoll(client); break;
            case GAME_QUERY_TYPE::MORTGAGE       : processMortgageProperty(client); break;
            case GAME_QUERY_TYPE::DEMORTGAGE     : processDemortgageProperty(client); break;
            case GAME_QUERY_TYPE::EXCHANGE       : processExchange(client); break;
            case GAME_QUERY_TYPE::BUILD          : processBuildBuildings(client); break;
            case GAME_QUERY_TYPE::SELL_BUILDINGS : processSellBuildings(client); break;
            case GAME_QUERY_TYPE::ACCEPT         : participateInExchange(client); break;
            default:
                this->updateThisClientWithQuery(QUERY::COMMAND_INDISPONIBLE, "Cette commande n'est pas disponible.", client);
                //client.send("Cette commande n'est pas disponible.");
                break;
        }
    }
    else{
        switch (query) {
            case GAME_QUERY_TYPE::PARTICIPATE : if (game.getAuctionStatus() == AuctionStatus::START) {for (auto &player : *game.getPlayers()) { if (player.getClient() == &client) { player.auctionStart(); } } participateInAuction(client); break; }
            default:
                this->updateThisClientWithQuery(QUERY::COMMAND_INDISPONIBLE, "Cette commande n'est pas disponible.", client);
                //client.send("Cette commande n'est pas disponible.");
                break;
        }
    }
}

/*
 * Boucle pour la faillite
 */
void GameServer::clientBankruptLoop(ClientManager &client) {
    //client.send("Vous avez fait faillite!\n");
    this->updateThisClientWithQuery(QUERY::HAS_BANKRUPT, "Vous avez fait faillite !", client);
    Player* current = game.getCurrentPlayer();

    while (current->getBankAccount()->getMoney() < 0 and current->getStatus() != PLAYER_STATUS::LOST){
        std::string str = "3 OPTIONS POSSIBLES : ";
        str += "\n -Hypothéquez vos propriétés restantes ( /mortgage )";
        str += "\n -Vendez vos propriétés ( /sell )";
        str += "\n -Abandonnez la partie ( /give-up )\n";
        updateThisClientWithQuery(QUERY::OPTIONS_WHEN_BANKRUPT, str, client);
        //client.send(str);

        GAME_QUERY_TYPE query = this->getGameQuery(client);
        switch (query) {
            case GAME_QUERY_TYPE::MORTGAGE :        // Same as under
            case GAME_QUERY_TYPE::SELL_BUILDINGS : processGameQueryBeforeRoll(client, query); break;
            case GAME_QUERY_TYPE::GIVE_UP : processBankruptcyToPlayer(); current->setStatus(PLAYER_STATUS::LOST); break;
            default:
                this->updateThisClientWithQuery(QUERY::COMMAND_INDISPONIBLE, "Cette commande n'est pas disponible.", client);
                break;
        }
    }

    if ( current->getBankAccount()->getMoney() >= 0 or current->getStatus() != PLAYER_STATUS::LOST ) {
        current->setStatus(PLAYER_STATUS::FREE);
        this->updateThisClientWithQuery(QUERY::NO_MORE_BANKRUPT, "Vous n'êtes plus en faillite! Continuez votre tour normalement.", client);
        //client.send("Vous n'êtes plus en faillite! Continuez votre tour normalement.");
    }
}

/*
 * Boucle qui dure tant que [auctionInProgress] est différent de [0].
 */
void GameServer::participateInAuction(ClientManager &client) {
    this->updateThisClientWithQuery(QUERY::PARTICIPATE_IN_AUCTION, "Vous participez à l'enchère!", client);
    //client.send("Vous participez à l'enchère!");
    while ( game.getAuctionStatus() != AuctionStatus::STOP ) { }
}

/*
 * Boucle qui dure tant que [getExchangeStatus] est différent de [0]
 */
void GameServer::participateInExchange(ClientManager &client) {
    game.setExchangeStatus(ExchangeStatus::OTHER);
    this->updateThisClientWithQuery(QUERY::PARTICIPATE_IN_EXCHANGE, "Vous participez à l'échange!", client);
    //client.send("Vous participez à l'échange!");
    while ( game.getExchangeStatus() != ExchangeStatus::STOP ) { }
}

/*
 * Boucle pour les enchères
 */
void GameServer::clientAuctionLoop(ClientManager &client, LandCell* land_cell) {

    Player* current = this->game.getCurrentPlayer();
    // Si ce n'est pas le tour du client
    if ( current->getClient() != &client ) { return; }

    //Déclaration de variables
    int bid = starting_bid;
    std::string str = "";

    // Starting auction
    str =  "\nUne enchère a débuté! La propriété concernée est la suivante: " + land_cell->getLand()->getName();
    str += "\n - Participez à l'enchère ( /participate ). (Obligatoire).";
    //str += "\n - Ne pas participez à l'enchère ( /out )\n";
    //this->updateAllClients(str);
    this->updateAllClientsWithQuery(QUERY::BEGIN_AUCTION, land_cell->getLand()->getName());


    if (current->getStatus() != PLAYER_STATUS::LOST or current->getBankruptingPlayer()->getStatus() != PLAYER_STATUS::LOST) {
        str = "Attention! Comme vous êtes à l'origine de cette enchère, vous participez par défaut.";
        str += "\nVeuillez attendre " + std::to_string(waiting_time_auction) + " secondes pour que les autres joueurs rejoignent.";
        //client.send(str);
        this->updateThisClientWithQuery(QUERY::WAIT_BEFORE_AUCTION_BEGIN, str, client);
    }

    game.startAuction();
    game.getCurrentPlayer()->auctionStart();
    sleep(waiting_time_auction);
    this->updateThisClientWithQuery(QUERY::FINISH_WAITING_TIME, "L'attente est terminée!", client);
    //client.send("L'attente est terminée!");
    game.setAuctionProgress(AuctionStatus::OTHER);

    Player* winner = nullptr;
    while ( winner == nullptr ) {
        for ( auto &player : *this->game.getPlayers() ) {
            winner = game.getAuctionWinner();
            if ( winner != nullptr ) {
                str = "Le joueur '" + player.getClient()->getAccount()->getUsername() + "' a remporté l'enchère !";
                this->updateAllClientsWithQuery(QUERY::WIN_AUCTION, player.getClient()->getAccount()->getUsername());
                //this->updateAllClients(str);

                // Make function WIN AUCTION
                player.acquireLand(land_cell->getLand());
                player.pay(bid);

                this->game.stopAuction();
                break; // return (serait aussi bon ici ?)
            }

            if ( player.isInAuction() and (player.getStatus() != PLAYER_STATUS::LOST or player.getStatus() != PLAYER_STATUS::BANKRUPT) ) {
                str =  "\nC'est au tour de '" + player.getClient()->getAccount()->getUsername() + "` d'enchérir !";
                str += "\nL'enchère est actuellement à " + std::to_string(bid);
                this->updateAllClientsWithQuery(QUERY::AUCTION_TURN, str);
                //this->updateAllClients(str);
                str = "";
                str += "\n - Enchérissez pour cette propriété ( /bid [montant] )";
                str += "\n - Quittez l'enchère et abandonner la propriété ( /out )";
                str += "\nToute erreur de commande entraine l'exclusion de l'enchère\n";

                //player.getClient()->send(str);
                QUERY query1 = QUERY::AUCTION_HOW_TO_BID;
                player.getClient()->sendQueryMsg(str, query1);
                //this->updateThisClientWithQuery(QUERY::AUCTION_HOW_TO_BID, str, client);

                GAME_QUERY_TYPE query;
                sf::Packet packet;
                player.getClient()->receive(query, packet);

                // Mauvaise commande
                if ( query != GAME_QUERY_TYPE::BID) {
                    player.leaveAuction();
                    str = player.getClient()->getAccount()->getUsername() + " est sorti(e) de l'enchère.";
                    this->updateAllClientsWithQuery(QUERY::HAS_LEAVE_AUCTION_WRONG_CMD, player.getClient()->getAccount()->getUsername());
                    //this->updateAllClients(str);
                }

                // Commande /bid [montant]
                if ( query == GAME_QUERY_TYPE::BID) {
                    std::string new_bid_s;
                    packet >> new_bid_s;
                    std::cout << "Un joueur à enchéri " << new_bid_s << "e pour une propriété" << std::endl;
                    int new_bid_i = std::stoi(new_bid_s);

                    // Nouvelle enchère inférieure au précédent
                    if ( new_bid_i <= bid ) {
                        player.leaveAuction();
                        str = player.getClient()->getAccount()->getUsername() + " est sorti(e) de l'enchère.";
                        str += "\nSa proposition était inférieur par rapport au minimum requis !";
                        //this->updateAllClients(str);
                        this->updateAllClientsWithQuery(QUERY::HAS_LEAVE_AUCTION_TO_LOW_BID, player.getClient()->getAccount()->getUsername());
                    }
                    // Le joueur ayant fait l'enchère n'as pas les fonds nécessaires
                    else if ( new_bid_i > player.getBankAccount()->getMoney() ) {
                        player.leaveAuction();
                        str = player.getClient()->getAccount()->getUsername() + " est sorti(e) de l'enchère.";
                        str += "\nIel ne possède pas les fonds nécessaire pour faire cette enchère !";
                        //this->updateAllClients(str);
                        this->updateAllClientsWithQuery(QUERY::HAS_LEAVE_AUCTION_TO_HIGH_BID, player.getClient()->getAccount()->getUsername());

                    }
                    // Tout s'est bien passé ! Il a pu enchérir !
                    else {
                        str = player.getClient()->getAccount()->getUsername() + " a surenchéri de ";
                        str += std::to_string(new_bid_i - bid) + "e !";
                        this->updateAllClientsWithQuery(QUERY::AUCTION_NEW_BID, str);
                        //this->updateAllClients(str);
                        bid = new_bid_i;
                    }
                }
            }
        }
    }
}




void GameServer::processEndTurn(ClientManager &client) {
    Player* current = game.getCurrentPlayer();
    // Si le joueur n'a pas encore lancé les dés ou qu'il est en prison, on lui notifie simplement de lancé les dés
    if (!current->hasRolled() or current->isInJail()) {
        this->updateAllClientsWithQuery(QUERY::ROLL_DICE_BEFORE_END_TURN, "Vous devez jeter les dés avant de finir votre tour.");
       //client.send("Vous devez jeter les dés avant de finir votre tour.");
        return;}
    // S'il a lancé les dés et qu'il n'est pas en prison alors c'est la fin de son tour, on reset le compteur de double et on change de joueur.
    this->game.getDice().resetDoubleCounter();
    this->game.endCurrentTurn();

    // On envoie des infos pour le ncurse
    this->sendGameData();
    this->sendBetterGameData();
}

/*
 * Gestion en cas de 3 doubles
 */
void GameServer::treeDouble(ClientManager& client) {
    Player* current = this->game.getCurrentPlayer();
    current->setRolled(true);
    this->updateThisClientWithQuery(QUERY::GO_TO_JAIL, " |-|-| Vous allez en prison |-|-| ", client);
    //client.send(" |-|-| Vous allez en prison |-|-| ");
    current->goToJail(this->game.getBoard()[PRISON_INDEX]);
}



void GameServer::processDemortgageProperty(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    this->updateThisClientWithQuery(QUERY::MESSAGE, "Veuillez sélectionner la propriété à déshypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriété.\n", client);
    //client.send("Veuillez sélectionner la propriété à déshypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des batiments.\n");
    while (query != GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){
        client.receive(query, packet);
        packet >> name;
        if (query == GAME_QUERY_TYPE::SELECT){
            LandCell* land_cell = game.getLandCell(name);
            if (land_cell != nullptr and land_cell->getLand()->getOwner() == game.getCurrentPlayer() and land_cell->getLand()->isMortgaged()){
                land_cell->getLand()->liftMortgage(game.getCurrentPlayer());
            }
            else {
                client.send("Cette propriété n'existe pas ou elle ne vous appartient pas ou n'est pas hypothéquée.\n");
            }
        }
        else {
            this->updateThisClientWithQuery(QUERY::MESSAGE, "Veuillez sélectionner la propriété à déshypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n", client);
            //client.send("Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n");
        }
    }
}

void GameServer::processMortgageProperty(ClientManager &client) { //for now, only works for bankruptcy if bankrupt player is the player whose turn it is.
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    this->updateThisClientWithQuery(QUERY::MESSAGE, "Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des batiments.\n", client);
    //client.send("Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des batiments.\n");
    while (query != GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){ //TODO check if no problem with undefined definition with while loop condition
        client.receive(query, packet); //todo check if problem if no package sent problem
        packet >> name;
        if (query == GAME_QUERY_TYPE::SELECT){
            LandCell* land_cell = game.getLandCell(name);
            if (land_cell != nullptr and land_cell->getLand()->getOwner() == game.getCurrentPlayer() and !land_cell->getLand()->isMortgaged()){
                land_cell->getLand()->mortgage(game.getCurrentPlayer());
            }
            else {
                client.send("Cette propriété n'existe pas ou elle ne vous appartient pas ou elle est déjà hypothéquée.\n");
            }
        }
        else {
            this->updateThisClientWithQuery(QUERY::MESSAGE, "Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n", client);
            //client.send("Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n");
        }
    }
}

void GameServer::processExchange(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    Player* exchange_player;
    int proposed_amount;
    std::string response = "\"La liste des joueurs disponibles pour un échange est la suivante: \\n\"";
    for (auto &player : *game.getPlayers()) {
        if (player.getStatus() != PLAYER_STATUS::BANKRUPT and &player != game.getCurrentPlayer()){
            response += std::string(player.getClient()->getAccount()->getUsername());        //TODO ça marche?
        }
    }
    this->updateThisClientWithQuery(QUERY::MESSAGE, response, client);
    //client.send(response);
    while (query != GAME_QUERY_TYPE::SELECT){
        this->updateThisClientWithQuery(QUERY::MESSAGE, "Pour choisir un joueur, utilisez /select nom d'utilisateur, pour annuler, tapez /leave.", client);
        //client.send("Pour choisir un joueur, utilisez /select nom d'utilisateur, pour annuler, tapez /leave.");
        client.receive(query, packet);
        packet >> name;
        exchange_player = getPlayerByUsername(name);
        if (exchange_player != nullptr or query == GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){
            break;
        }
        else {
            this->updateThisClientWithQuery(QUERY::MESSAGE, "Nom de joueur invalide, veuillez réessayer.\n", client);
            //client.send("Nom de joueur invalide, veuillez réessayer.\n");
            query = GAME_QUERY_TYPE::NONE;
        }
    }
    if (GAME_QUERY_TYPE::LEAVE_SELECTION_MODE == query){
        client.send("Vous quittez à présent l'interface d'échange.\n");
    }
    else if (GAME_QUERY_TYPE::SELECT == query){
        client.send("Voici les propriétés disponibles pour l'échange:\n");
        client.send(exchange_player->getStringOfAllProperties());
        client.send("Pour sélectionner la proriété ou carte que vous souhaitez aquérir, tapez /select nom de la propriété.");
        query = GAME_QUERY_TYPE::NONE;
        while (GAME_QUERY_TYPE::SELECT != query) {
            client.receive(query, packet);
            packet >> name;
            LandCell* land_cell = game.getLandCell(name);
            if (land_cell != nullptr and land_cell->getLand()->getOwner() == exchange_player) {
                client.send("Propriété sélectionée!");
                client.send("Quel montant proposez-vous pour le rachat de cette propriété?\n Utilisez /select montant (ça doit être plus que 0).");
                client.receive(query, packet);
                packet >> name;
                while (true){
                    try {
                        proposed_amount = std::stoi(name);
                        if (proposed_amount <= game.getCurrentPlayer()->getBankAccount()->getMoney() and proposed_amount > 0){
                            break;
                        }
                        else {
                            client.send("Vous n'avez pas assez d'argent pour proposer ce montant ou montant < 0.\n");
                        }
                    } catch (const std::invalid_argument& e) {
                        client.send("Invalid amount.\n");
                        break;
                    }
                }
                game.setExchangeStatus(ExchangeStatus::START);
                if (proposeExchange(*game.getCurrentPlayer(), *exchange_player, land_cell->getLand(), proposed_amount)){
                    exchange_player->removeLand(land_cell->getLand());
                    game.getCurrentPlayer()->acquireLand(land_cell->getLand());
                    game.getCurrentPlayer()->pay(proposed_amount);
                    exchange_player->receive(proposed_amount, std::string(game.getCurrentPlayer()->getClient()->getAccount()->getUsername()));
                    land_cell->getLand()->setOwner(game.getCurrentPlayer());
                    client.send("Votre proposition a été acceptée!.\n");
                }
                else{
                    client.send("Votre proposition a été refusée.\n");
                }
                client.send("L'échange est terminé.");
                exchange_player->getClient()->send("L'échange est terminé.");
                game.setExchangeStatus(ExchangeStatus::STOP);
            }
            else {
                client.send("Cette propriété n'est pas valide");
                client.send("Vous quittez le module de proposition d'échange. Pour proposer un échange, tapez à nouveau /exchange.");
            }
        }
    }
    else {
        client.send("Error 1.");
    }
}

void GameServer::processBuildBuildings(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    client.send("Où voulez-vous construire? Selectionnez la propriété avec /select nom de la propriété.\n");
    while (true){
        client.send("Pour quitter le mode de sélection de propriétés. Tapez /leave.\n");
        client.receive(query, packet);
        if (query == GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){
            client.send("Vous quittez l'interface de sélection de propriétés.");
            break;
        }
        packet >> name;
        Land* land = getLandByName(name);
        if (land == nullptr){
            client.send("Cette propriété n'existe pas");
        }
        else{
            Property* p = dynamic_cast<Property*>(land);
            if (p != nullptr and p->build(game.getCurrentPlayer())){
                client.send("Vous avez construit un batiment.\n");
            }
            else {
                client.send("Building failed.\n");
            }
        }
    }
}

void GameServer::processSellBuildings(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    client.send(
            "Sélectionnez une propriété sur laquelle vendre un bâtiment avec la commande /select nom de la propriété.\n");
    while (true) {
        client.send("Pour quitter le mode de sélection de propriétés. Tapez /leave.\n");
        client.receive(query, packet);
        if (query == GAME_QUERY_TYPE::LEAVE_SELECTION_MODE) {
            break;
        }
        packet >> name;
        Land *land = getLandByName(name);
        if (land == nullptr){
            client.send("Cette propriété n'existe pas");
        }
        else{
            Property *p = dynamic_cast<Property *>(land);
            if (p != nullptr and p->sellBuilding(game.getCurrentPlayer())) {
                client.send("Vous avez vendu un bâtiment.\n");
            } else {
                client.send("Selling failed.\n");
            }
        }
    }
}

bool GameServer::proposeExchange(Player &proposing_player, Player &proposed_to_player, Land *land, int amount) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string response;
    std::string comm_string = "";
    comm_string += (std::string(proposing_player.getClient()->getAccount()->getUsername()) + "vous propose " + std::to_string(amount) + " pour votre possession nommée " + land->getName());
    proposed_to_player.getClient()->send("Tapez /accept pour entretenir l'offre (c'est obligatoire).");
    while (game.getExchangeStatus() != ExchangeStatus::OTHER) {}
    proposed_to_player.getClient()->send(comm_string);
    while (true) {
        proposed_to_player.getClient()->send("Pour accepter, tapez /select yes, sinon tapez /select no.");
        proposed_to_player.getClient()->receive(query, packet);
        packet >> response;
        if (query == GAME_QUERY_TYPE::SELECT){
            if (response == "yes"){
                return true;
            }
            else if (response == "no"){
                return false;
            }
        }
    }
}

void GameServer::processBankruptcyToPlayer(){
    for (auto property : game.getCurrentPlayer()->getAllProperties()){
        property->setOwner(game.getCurrentPlayer()->getBankruptingPlayer());
        game.getCurrentPlayer()->getBankruptingPlayer()->acquireProperty(*property);
    }
    for (auto company : game.getCurrentPlayer()->getAllCompanies()){
        company->setOwner(game.getCurrentPlayer()->getBankruptingPlayer());
        game.getCurrentPlayer()->getBankruptingPlayer()->acquireCompany(*company);
    }
    for (auto station : game.getCurrentPlayer()->getAllStations()){
        station->setOwner(game.getCurrentPlayer()->getBankruptingPlayer());
        game.getCurrentPlayer()->getBankruptingPlayer()->acquireStation(*station);
    }
    for (auto GOOJ_cards : game.getCurrentPlayer()->getAllGOOJCards()){
        GOOJ_cards->setOwner(game.getCurrentPlayer()->getBankruptingPlayer());
        game.getCurrentPlayer()->getBankruptingPlayer()->acquireGOOJCard(GOOJ_cards);
    }
}

Land *GameServer::getLandByName(std::string &name) {
    LandCell* land_cell = game.getLandCell(name);
    if (land_cell == nullptr){
        return nullptr;
    }
    Land* land = land_cell->getLand();
    return land;
}

void GameServer::updateAllClients(std::string update) {
    for ( auto client : clients ) {
        client->send(update);
    }
}

void GameServer::updateAllClientsWithQuery(QUERY &&query, std::string update) {
    std::cout << clients.size() << " number of client for the loop (updateAllClientsWithQuery)" << std::endl;
    for ( auto client : clients ) {
        client->sendQueryMsg(update, query);
    }
}

void GameServer::updateThisClientWithQuery(QUERY &&query, std::string update, ClientManager &client) {
    client.sendQueryMsg(update, query);
}

int GameServer::getCode() const { return code.getCode(); }

Player* GameServer::getPlayerByUsername(std::string &name) {
    Player* ret_player = nullptr;
    for (auto &player : *game.getPlayers()){
        if (player.getClient()->getAccount()->getUsername() == name){
            ret_player = &player;
            return ret_player;
        }
    }
    return ret_player;
}

Capitalist* GameServer::getGame(){
    return &game;
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

bool GameServer::isClientAdmin(ClientManager &client) {return (game.getPlayer(client)->isAdmin());}

bool GameServer::isCode(int other) const { return code.getCode() == other; }




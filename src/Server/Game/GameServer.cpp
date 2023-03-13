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

/*
 * Return a string with the exact maxLength size.
 * str < maxLength -> add ' '
 * str > maxLength -> trim excédent character
 */
std::string refactorToAMaxLengthString(std::string str, int maxLength) {
    if (static_cast<int>(str.size()) < maxLength) {
        int space = maxLength - str.size();
        for (int i = 0; i < space; i++ ) {str += " ";}
        return str;
    }
    else {
        std::string new_str = "";
        for (int i = 0; i < maxLength; i ++) {
            new_str += str[i];
        }
        return new_str;
    }
}

/*
 * SHow the game infos formatted for better visibility on the terminal
 */
void GameServer::boardInfos() {
    std::string str = "";
    str += "+—————————CAPITALI$T————————+\n";
    // Loop for all the players
    for (auto &player : *this->game.getPlayers()) {
        // Player + Position + Money
        std::string username = refactorToAMaxLengthString(player.getClient()->getAccount()->getUsername(),6);
        std::string position = refactorToAMaxLengthString(std::to_string(player.getCurrentCell()->getPosition()), 8);
        std::string money = refactorToAMaxLengthString(std::to_string(player.getBankAccount()->getMoney()),5);
        str += "| PLAYER | POSITION | MONEY |\n";
        str += "| " + username + " | " + position + " | " + money + " |\n";

        // Loop for all the player's properties
        if (player.getAllProperties().size() > 0) { str += "|PROPERTIES           LEVEL |\n"; }
        for (auto property : player.getAllProperties()) {
            std::string prop = refactorToAMaxLengthString(property->getName(),8);
            std::string level = refactorToAMaxLengthString(std::to_string(property->getIntLevel()), 5);
            str += "|        | " + prop + " | " + level + " |\n";
        }

        // Loop for all the player's compagnie
        if (player.getAllCompanies().size() > 0) { str += "|COMPANIES            MULTI |\n"; }
        for (auto property : player.getAllCompanies()) {
            std::string prop = refactorToAMaxLengthString(property->getName(), 8);
            int multiInt = (player.getAllCompanies().size() == 2) ? 12 : 5;
            std::string multiString = refactorToAMaxLengthString(std::to_string(multiInt), 5);
            str += "|        | " + prop + " | " + multiString + " |\n";
        }

        // Loop for all the player's stations
        if (player.getAllStations().size() > 0) { str += "|STATIONS           LEVEL |\n"; }
        for (auto property : player.getAllStations()) {
            std::string prop = property->getName();
            str += "| " + refactorToAMaxLengthString(" ", 6) + " | ";
            str += refactorToAMaxLengthString(prop, 8)  + " | ";
            str += refactorToAMaxLengthString(" ", 5) + " |\n";
        }
        str += "+———————————————————————————+\n";
    }
    std::string nextTurn = refactorToAMaxLengthString(game.getCurrentPlayer()->getClient()->getAccount()->getUsername(), 10);
    str += "| A '" + nextTurn + "' de jouer ! |\n";
    str += "+———————————————————————————+\n";

    this->updateAllClients(str);
}

/*
 * Send Start infos formatted for the n-curse terminal
 */
void GameServer::sendStartInfo() {
    std::string ret = "START_INFOS:\n";
    //Indexe + Nb_player
    std::string nb_player = std::to_string(game.getPlayers()->size());
    ret += "n:" + nb_player + ";";

    // Indexe + username
    for ( auto &player : *game.getPlayers() ) {
        std::string indexe = std::to_string(player.getIndex());
        std::string username = player.getClient()->getAccount()->getUsername();
        ret += "P" + indexe + ":" + username + ";";
    }
    this->updateAllClients(ret);
}

/*
 * Send data formatted for the n-curse terminal
 */
void GameServer::sendAllGameData(){
    std::string ret = "GM-";

    // Player Index + Position + BankAccount + JailCard Possessed.
    for (auto &player : *game.getPlayers()){
        std::string indexe =    std::to_string(player.getIndex());
        std::string position =  std::to_string(player.getCurrentCell()->getPosition());
        std::string money =     std::to_string(player.getBankAccount()->getMoney());
        std::string jailCard =  std::to_string(player.getAllGOOJCards().size());
        ret += ("P" + indexe + ": pos-" + position + ",ba-" + money) + ",j-" + jailCard + ";";
    }
    ret += "\n";

    // Player Indexe + {Properties possessed + level + mortgage}
    for (auto &player : *game.getPlayers()) {
        std::string indexe = std::to_string(player.getIndex());
        ret += ("P" + indexe + ": properties-");

        for (auto property : player.getAllProperties()){
            std::string level = std::to_string(property->getIntLevel());
            std::string mortgage = (property->isMortgaged()) ? "n," : "y,";
            ret += property->getName() + ",level-" + level + ",h-" + mortgage;
        }
        // Station
        for (auto station : player.getAllStations()){ret += station->getName() + ".";}
        // Compagnie
        for (auto company : player.getAllCompanies()){ret += company->getName() + ".";}
        ret += ";";
    }
    this->updateAllClients(ret);
}

/*
 * Renvoie une GAME_QUERY obtenue depuis un client.receive().
 */
GAME_QUERY_TYPE GameServer::getGameQuery(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    client.receive(query);
    return query;
}


void GameServer::clientLoop(ClientManager &client) {
	std::cout << client.getAccount()->getUsername() << " has join a game with code : " << this->code.getCode() << std::endl;
    updateAllClients("Le joueur " + client.getAccount()->getUsername() + " a rejoint la partie!");
    client.send("Le code de cette partie est " + std::to_string(this->code.getCode()) + ". Partagez-le avec tous vos amis!");
	while (this->active) {

        // if player is in jail
        /*
        if (game.getCurrentPlayer()->isInJail()){
            game.getCurrentPlayer()->getCurrentCell()->action(game.getCurrentPlayer());
        }
         */
        //else {
                if (game.getCurrentPlayer()->getPlayerStatus() == PLAYER_STATUS::LOST and game.getCurrentPlayer()->getClient() == &client){
                    int index_counter = 0;
                    for (auto &player : *game.getPlayers()){
                        if (player.getPlayerStatus() == PLAYER_STATUS::LOST){
                            clients.erase(clients.begin()+index_counter);
                            *game.getPlayers()->erase(game.getPlayers()->begin() + index_counter);
                            break;
                        }
                        index_counter++;
                    }
                    break;
                }
                if (game.getPlayers()->size() == 1 and game.isRunning()){
                    client.send("Vous avez gagné!");
                }
                clientBeforeRollLoop(client);
        //}
            // TODO after roll loop
        /*
		GAME_QUERY_TYPE query;
		sf::Packet packet;
		game.receiveQuery(query, packet);
		if (query == GAME_QUERY_TYPE::LEAVE) { break; }
         TODO manage leave game
         */
	}
    updateAllClients("Le joueur " + std::string(game.getCurrentPlayer()->getClient()->getAccount()->getUsername()) + " a fait faillite et est donc disqualifié de la partie!");
}


/*
 * Boucle dans laquelle un client est envoyé
 */
void GameServer::clientBeforeRollLoop(ClientManager &client) {
    while ( true ) {
        // Récupération de la query et du player actuel
        GAME_QUERY_TYPE query = this->getGameQuery(client);
        Player* current = this->game.getCurrentPlayer();

        // Si la commande est /start
        if ( query == GAME_QUERY_TYPE::START ) { this->processStart(client); continue; }

        // Si la partie n'est pas encore lancée
        if ( !this->game.isRunning() ) { client.send("La partie n'est pas encore lancée."); continue; }

        // Si le [client doit jouer] OU qu'il y a une [enchère] OU qu'il y a un [échange]
        if ( current->getClient() == &client or this->game.auctionInProgress() == 1 or this->game.getExchangeStatus() == 1 ) {

            // ProcessBeforeRoll
            this->processGameQueryBeforeRoll(client, query);

            // Si le joueur a [lancé les dés] ET qu'il n'est pas en status [!perdu]
            if ( current->hasRolled() and current->getPlayerStatus() != PLAYER_STATUS::LOST ) {
                client.send("Plus aucune commande ne vous est disponible ce tour ci. Votre tour s'est donc automatiquement terminé.");
                processEndTurn(client);
                break;
            }
            // Si le joueur est en status [perdu]
            if ( current->getPlayerStatus() == PLAYER_STATUS::LOST ) {
                client.send("Vous avez perdu :(");
                break;
            }
        }
        // Si ce n'est [pas au client de jouer] ET qu'il n'y a pas [d'enchère] ET qu'il n'y a pas [d'échange]
        client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour.");
    }
}

/*
 * Permet de connecter le client à la partie
 * Et d'ajouter le pointeur vers le serveur au client
 */
void GameServer::connectClientToThisGame(ClientManager* client) {
    this->clients.push_back(client);
    client->setGameServer(this);
}

/*
 * Process une Game_Query
 */
/*
void GameServer::processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query) {
    if (this->game.auctionInProgress()) {
        switch ( query ) {
            case GAME_QUERY_TYPE::PARTICIPATE : if (game.auctionInProgress() == 1) { participateInAuction(client); }
                                                else {client.send("Cette commande n'est pas disponible."); }
                                                break;
            case GAME_QUERY_TYPE::LEAVE_BID :   if (game.auctionInProgress() == 1) {
                                                    for (auto &player : *game.getPlayers()) {
                                                        if (player.getClient() == &client) { player.leaveAuction(); }
                                                    }
                                                }
                                                break;
            default: client.send("Cette commande n'est plus disponible, vous avez trop tardé."); break;
        }
        return;
    }
    switch (query) {
        case GAME_QUERY_TYPE::END_TURN       : processEndTurn(client);          break;
        case GAME_QUERY_TYPE::ROLL_DICE      : processDiceRoll(client);         break;
        case GAME_QUERY_TYPE::MORTGAGE       : processMortgageProperty(client); break;
        case GAME_QUERY_TYPE::DEMORTGAGE     : processDemortgageProperty(client); break;
        case GAME_QUERY_TYPE::EXCHANGE       : processExchange(client);         break;
        case GAME_QUERY_TYPE::BUILD          : processBuildBuildings(client);   break;
        case GAME_QUERY_TYPE::SELL_BUILDINGS : processSellBuildings(client);    break;
        case GAME_QUERY_TYPE::ACCEPT         : participateInExchange(client);   break;
        default: client.send("Cette commande n'est pas disponible.");           break;
    }
}
*/
void GameServer::processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query) {
    if (!game.auctionInProgress()) {
        switch (query) {
            case GAME_QUERY_TYPE::END_TURN       : processEndTurn(client); break;
            case GAME_QUERY_TYPE::ROLL_DICE      : processDiceRoll(client); break;
            case GAME_QUERY_TYPE::MORTGAGE       : processMortgageProperty(client); break;
            case GAME_QUERY_TYPE::DEMORTGAGE     : processDemortgageProperty(client); break;
            case GAME_QUERY_TYPE::EXCHANGE       : processExchange(client); break;
            case GAME_QUERY_TYPE::BUILD          : processBuildBuildings(client); break;
            case GAME_QUERY_TYPE::SELL_BUILDINGS : processSellBuildings(client); break;
            case GAME_QUERY_TYPE::ACCEPT         : participateInExchange(client); break;
            default: client.send("Cette commande n'est pas disponible."); break;
        }
    }
    else{
        switch (query) {
            case GAME_QUERY_TYPE::PARTICIPATE : if (game.auctionInProgress() == 1) { participateInAuction(client); } else {client.send("Cette commande n'est pas disponible.");} break;
            case GAME_QUERY_TYPE::LEAVE_BID : if (game.auctionInProgress() == 1) { for (auto &player : *game.getPlayers()) { if (player.getClient() == &client) { player.leaveAuction(); } } } break;
            default: client.send("Cette commande n'est plus disponible, vous avez trop tardé."); break;
        }
    }
}

/*
 * Boucle pour la faillite
 */
void GameServer::clientBankruptLoop(ClientManager &client) {
    client.send("Vous avez fait faillite!\n");
    Player* current = game.getCurrentPlayer();

    while (current->getBankAccount()->getMoney() < 0 and current->getPlayerStatus() != PLAYER_STATUS::LOST){
        std::string str = "3 OPTIONS POSSIBLES : ";
        str += "\n -Hypothéquez vos propriétés restantes ( /mortgage )";
        str += "\n -Vendez vos propriétés ( /sell )";
        str += "\n -Abandonnez la partie ( /give-up )\n";
        client.send(str);

        GAME_QUERY_TYPE query = this->getGameQuery(client);
        switch (query) {
            case GAME_QUERY_TYPE::MORTGAGE :        // Same as under
            case GAME_QUERY_TYPE::SELL_BUILDINGS : processGameQueryBeforeRoll(client, query); break;
            case GAME_QUERY_TYPE::GIVE_UP : processBankruptcyToPlayer(); current->setPlayerStatus(PLAYER_STATUS::LOST); break;
            default: client.send("Cette commande n'est pas disponible.\n"); break;
        }
    }

    if ( current->getBankAccount()->getMoney() >= 0 or current->getPlayerStatus() != PLAYER_STATUS::LOST ) {
        current->setPlayerStatus(PLAYER_STATUS::FREE);
        client.send("Vous n'êtes plus en faillite! Continuez votre tour normalement.\n");
    }
}

/*
 * Boucle qui dure tant que [auctionInProgress] est différent de [0].
 */
void GameServer::participateInAuction(ClientManager &client) {
    client.send("Vous participez à l'enchère!");
    while ( game.auctionInProgress() != 0 ) { }
}

/*
 * Boucle qui dure tant que [getExchangeStatus] est différent de [0]
 */
void GameServer::participateInExchange(ClientManager &client) {
    game.setExchangeStatus(2);
    client.send("Vous participez à l'échange!");
    while ( game.getExchangeStatus() != 0 ) { }
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
    str += "\n - Participez à l'enchère ( /participate )";
    str += "\n - Ne pas participez à l'enchère ( /out )\n";
    this->updateAllClients(str);

    if (current->getPlayerStatus() != PLAYER_STATUS::LOST or current->getBankruptingPlayer()->getPlayerStatus() != PLAYER_STATUS::LOST) {
        str = "Attention! Comme vous êtes à l'origine de cette enchère, vous participez par défaut.";
        str += "\nVeuillez attendre " + std::to_string(waiting_time_auction) + " secondes pour que les autres joueurs rejoignent.";
        client.send(str);
    }

    game.startAuction();
    sleep(waiting_time_auction);
    client.send("L'attente est terminée!");
    game.setAuctionProgress(2);

    Player* winner = nullptr;
    while ( winner == nullptr ) {
        for ( auto &player : *this->game.getPlayers() ) {
            winner = game.identifyAuctionWinner();
            if ( winner != nullptr ) {
                str = "Le joueur '" + player.getClient()->getAccount()->getUsername() + "' a remporté l'enchère !";
                updateAllClients(str);

                // Make function WIN AUCTION
                player.acquireLand(land_cell->getLand());
                player.pay(bid);

                this->game.stopAuction();
                break; // return (serait aussi bon ici ?)
            }

            if ( player.isInAuction() and (player.getPlayerStatus() != PLAYER_STATUS::LOST or player.getPlayerStatus() != PLAYER_STATUS::BANKRUPT) ) {
                str =  "\nC'est au tour de '" + player.getClient()->getAccount()->getUsername() + "` d'enchérir !";
                str += "\nL'enchère est actuellement à " + std::to_string(bid);
                str += "\n - Enchérissez pour cette propriété ( /bid [montant] )";
                str += "\n - Quittez l'enchère et abandonner la propriété ( /out )";
                str += "\nToute erreur de commande entraine l'exclusion de l'enchère\n";
                this->updateAllClients(str);

                GAME_QUERY_TYPE query;
                sf::Packet packet;
                player.getClient()->receive(query, packet);

                // Mauvaise commande
                if ( query != GAME_QUERY_TYPE::BID) {
                    player.leaveAuction();
                    str = player.getClient()->getAccount()->getUsername() + " est sorti(e) de l'enchère.";
                    updateAllClients(str);
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
                        this->updateAllClients(str);
                    }
                    // Le joueur ayant fait l'enchère n'as pas les fonds nécessaires
                    else if ( new_bid_i > player.getBankAccount()->getMoney() ) {
                        player.leaveAuction();
                        str = player.getClient()->getAccount()->getUsername() + " est sorti(e) de l'enchère.";
                        str += "\nIel ne possède pas les fonds nécessaire pour faire cette enchère !";
                        this->updateAllClients(str);
                    }
                    // Tout s'est bien passé ! Il a pu enchérir !
                    else {
                        str = player.getClient()->getAccount()->getUsername() + " a surenchéri de ";
                        str += std::to_string(new_bid_i - bid) + "e !";
                        this->updateAllClients(str);
                        bid = new_bid_i;
                    }
                }
            }
        }
    }
}

/*
 * Démarre la partie si c'est possible
 */
void GameServer::processStart(ClientManager &client) {
    if (this->game.isRunning())               { client.send("La partie est déjà en cours !"); return; }
    if (!this->isClientAdmin(client))         { client.send("Vous n'êtes pas administrateur."); return; }
    if (this->game.getNumberOfPlayers() <= 1) { client.send("Vous êtes seul dans la partie, invitez un autre joueur pour lancer la partie."); return; }
    this->game.startGame();
    sendStartInfo();
    this->updateAllClients("Lancement de la partie !");
}


void GameServer::processEndTurn(ClientManager &client) {
    Player* current = game.getCurrentPlayer();
    // Si le joueur n'a pas encore lancé les dés ou qu'il est en prison, on lui notifie simplement de lancé les dés
    if (!current->hasRolled() or current->isInJail()) {client.send("Vous devez jeter les dés avant de finir votre tour."); return;}
    // S'il a lancé les dés et qu'il n'est pas en prison alors c'est la fin de son tour, on reset le compteur de double et on change de joueur.
    this->game.getDice().resetDoubleCounter();
    this->game.endCurrentTurn();

    // TODO : On envoie des infos pour le ncurse
    this->sendAllGameData();
    this->boardInfos();
}

/*
 * Gestion en cas de 3 doubles
 */
void GameServer::treeDouble(ClientManager& client) {
    Player* current = this->game.getCurrentPlayer();
    current->setRolled(true);
    client.send(" |-|-| Vous allez en prison |-|-| ");
    current->goToJail(this->game.getBoard()->getCellByIndex(PRISON_INDEX));
}

/*
 * Processus du lancement de dés jusqu'à l'exécution de l'action de la carte
 * Gestion des doubles
 * Gestion des enchères (debut)
 */
void GameServer::processDiceRoll(ClientManager &client) {
    std::string str = "";
    Player* current = game.getCurrentPlayer();

    // Lancement des dés
    int roll_result_i = current->roll(game.getDice());

    // Déplacement du joueur
    int new_cell_idx = (current->getPosition() + roll_result_i) % BOARD_SIZE;
    Cell* new_cell = this->game.getBoard()->getCellByIndex(new_cell_idx);
    current->move(new_cell);

    // Message terminal
    str = "\n" + client.getAccount()->getUsername() + " a jeté les dés et obtenu un [" + std::to_string(roll_result_i) + "]";
    str += "\nIel est arrivé sur la case [" + std::to_string(new_cell_idx) + "]";
    str += (game.rolledADouble()) ? "\nC'est un double ! Iel pourra rejouer !\n" : "\n";
    updateAllClients(str);

    //Gestion des doubles (Si trois doubles go prison)
    if ( game.rolledADouble() ) { current->setRolled(false); }
    if ( game.getDice().getDoubleCounter() == 3 ) { this->treeDouble(client); return; }

    // Action de la case sur laquelle il est tombé.
    current->getCurrentCell()->action(game.getCurrentPlayer());

    // TODO DMD A JOACHIM ?? getBankruptingPlayer() ?? (rémy)
    // SI le joueur est en faillite
    if (current->getPlayerStatus() == PLAYER_STATUS::BANKRUPT and current->getBankruptingPlayer() != nullptr) { clientBankruptLoop(client); }

    // Si le joueur a perdu
    if (current->getPlayerStatus() == PLAYER_STATUS::LOST) { return; }

    LandCell *land_cell = dynamic_cast<LandCell*>(current->getCurrentCell());

    // Si le dynamic cast n'a pas fonctionné
    if (land_cell == nullptr) { return; }

    // TODO faire payer ?? JOACHIM ?? (rémy)
    // Si la propriété à déjà un propriétaire
    if (land_cell->getLand()->getOwner() != nullptr) { return; }

    // Lancement d'une enchère
    updateAllClients("\n\n$$$ AUCTION STARTING $$$");
    clientAuctionLoop(client, land_cell);
}

void GameServer::processDemortgageProperty(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    client.send("Veuillez sélectionner la propriété à déhypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des batiments.\n");
    while (query != GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){
        client.receive(query, packet);
        packet >> name;
        if (query == GAME_QUERY_TYPE::SELECT){
            LandCell* land_cell = game.getCellByName(name);
            if (land_cell != nullptr and land_cell->getLand()->getOwner() == game.getCurrentPlayer() and land_cell->getLand()->isMortgaged()){
                land_cell->getLand()->liftMortgage(game.getCurrentPlayer());
            }
            else {
                client.send("Cette propriété n'existe pas ou elle ne vous appartient pas ou n'est pas hypothéquée.\n");
            }
        }
        else {
            client.send("Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n");
        }
    }
}

void GameServer::processMortgageProperty(ClientManager &client) { //for now, only works for bankruptcy if bankrupt player is the player whose turn it is.
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    client.send("Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des batiments.\n");
    while (query != GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){ //TODO check if no problem with undefined definition with while loop condition
        client.receive(query, packet); //todo check if problem if no package sent problem
        packet >> name;
        if (query == GAME_QUERY_TYPE::SELECT){
            LandCell* land_cell = game.getCellByName(name);
            if (land_cell != nullptr and land_cell->getLand()->getOwner() == game.getCurrentPlayer() and !land_cell->getLand()->isMortgaged()){
                land_cell->getLand()->mortgage(game.getCurrentPlayer());
            }
            else {
                client.send("Cette propriété n'existe pas ou elle ne vous appartient pas ou elle est déjà hypothéquée.\n");
            }
        }
        else {
            client.send("Veuillez sélectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n");
        }
    }
}

void GameServer::processExchange(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    Player* exchange_player;
    int proposed_amount;
    client.send("La liste des joueurs disponibles pour un échange est la suivante: \n");
    std::string response = "";
    for (auto &player : *game.getPlayers()) {
        if (player.getPlayerStatus() != PLAYER_STATUS::BANKRUPT and &player != game.getCurrentPlayer()){
            response += std::string(player.getClient()->getAccount()->getUsername());        //TODO ça marche?
        }
    }
    client.send(response);
    while (query != GAME_QUERY_TYPE::SELECT){
        client.send("Pour choisir un joueur, utilisez /select nom d'utilisateur, pour annuler, tapez /leave.");
        client.receive(query, packet);
        packet >> name;
        exchange_player = getPlayerByUsername(name);
        if (exchange_player != nullptr or query == GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){
            break;
        }
        else {
            client.send("Nom de joueur invalide, veuillez réessayer.\n");
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
            LandCell* land_cell = game.getBoard()->getCellByName(name);
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
                game.setExchangeStatus(1);
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
                game.setExchangeStatus(0);
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
    while (game.getExchangeStatus() != 2) {}
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
    LandCell* land_cell = game.getBoard()->getCellByName(name);
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

void GameServer::addPlayer(ClientManager &client) {
    this->game.addPlayer(client);
    this->game.getPlayers()->at(game.getPlayers()->size() - 1).setIndex(game.getPlayers()->size() - 1);
}

bool GameServer::isClientAdmin(ClientManager &client) {return (game.getPlayerByClient(client)->isAdmin());}

bool GameServer::isCode(int other) const { return code.getCode() == other; }




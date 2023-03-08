#include "GameServer.hpp"
#include "../../Game/Board/Obtainable/Cells/LandCell.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"
#include "../../Game/Board/Obtainable/Cells/Land/Land.hpp"
#include "string.h"
#include "Timer.hpp"
#include "../../Game/Capitalist.hpp"
#include <string>

#include <stdlib.h>
#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <stdexcept>


void GameServer::sendStartInfo() {
    std::string ret = "START_INFOS:\n";
    // Nbr player;
    ret += "n:" + std::to_string(game.getPlayers()->size()) + ";";
    for ( auto &player : *game.getPlayers() ) {
        ret += "P" + std::to_string(player.getIndex()) + ":" + player.getClient()->getAccount()->getUsernameString() + ";";
    }
    for (auto client : clients){
        client->send(ret);
    }

}
void GameServer::sendAllGameData(){
    int counter = 0;
    std::string ret = "GM-";
    for (auto &player : *game.getPlayers()){
        ret += ("P" + std::to_string(player.getIndex()) + ": pos-" + std::to_string(player.getCurrentCell()->getPosition()) + ",ba-" + std::to_string(player.getBankAccount()->getMoney()));
        ret += ",j-" + std::to_string(player.getAllGOOJCards().size()) + ";";
    }
    ret += "\n";
    for (auto &player : *game.getPlayers()){
        ret += ("P" + std::to_string(player.getIndex()) + ": properties-");
        for (auto property : player.getAllProperties()){
            ret += property->getName() + ",level-" + std::to_string((int) property->getLevel()) + ",h-";
            if (property->isMortgaged()){ret += "n,";}
            else {ret += "y,";}
        }
        for (auto station : player.getAllStations()){
            ret += station->getName() + ".";
        }
        for (auto company : player.getAllCompanies()){
            ret += company->getName() + ".";
        }
        ret += ";";
    }

    for (auto client : clients){
        client->send(ret);
    }
}

void GameServer::clientLoop(ClientManager &client) {
	std::cout << client.getAccount()->getUsername() << " has join a game with code : " << this->code.getCode() << std::endl;
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
                if (game.getPlayers()->size() == 1){
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

void GameServer::clientBeforeRollLoop(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    while (true) {
        // Récupération de l'information
        sf::Packet packet;
        client.receive(query);

        if ( query == GAME_QUERY_TYPE::START ) { processStart(client); }
        else if ( &client == game.getCurrentPlayer()->getClient() or game.auctionInProgress() == 1 ) {
            if ( game.isRunning() ) {
                processGameQueryBeforeRoll(client, query);
                if (game.getCurrentPlayer()->hasRolled() and game.getCurrentPlayer()->getClient() == &client and game.getCurrentPlayer()->getPlayerStatus() != PLAYER_STATUS::LOST){
                    client.send("Plus aucune commande ne vous est disponible ce tour ci. Votre tour s'est donc automatiquement terminé.");
                    processEndTurn(client);
                    break;
                }
                else if (game.getCurrentPlayer()->getPlayerStatus() == PLAYER_STATUS::LOST){
                    client.send("Vous avez perdu :(");
                    break;
                }
            }
            else { client.send("La partie n'est pas encore lancée."); }
        }
        else { client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour."); }
        query = GAME_QUERY_TYPE::NONE;
    }
}

void GameServer::addClient(ClientManager* client) {
	this->clients.push_back(client);
	client->setGameServer(this);
}


/* OBSOLETE
void GameServer::processGameQuery(ClientManager &client, GAME_QUERY_TYPE query){
    if (GAME_QUERY_TYPE::START == query) processStart(client);
    else {
        if (&client == game.getCurrentPlayer()->getClient()){
            switch(query){
                case GAME_QUERY_TYPE::END_TURN: processEndTurn(client); break;
                case GAME_QUERY_TYPE::ROLL_DICE: processDiceRoll(client); break;
            }
        }
        else {
            client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour.");
        }
    }
}
*/

void GameServer::processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query) {
    if (!game.auctionInProgress()){
        switch (query) {
            case GAME_QUERY_TYPE::END_TURN : processEndTurn(client); break;
            case GAME_QUERY_TYPE::ROLL_DICE : processDiceRoll(client); break;
            case GAME_QUERY_TYPE::MORTGAGE : processMortgageProperty(client); break;
            case GAME_QUERY_TYPE::DEMORTGAGE : processMortgageProperty(client); break;
            case GAME_QUERY_TYPE::EXCHANGE : processExchange(client); break;
            case GAME_QUERY_TYPE::BUILD : processBuildBuildings(client); break;
            case GAME_QUERY_TYPE::SELL_BUILDINGS : processSellBuildings(client); break;
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

void GameServer::clientBankruptLoop(ClientManager &client) {
    GAME_QUERY_TYPE query;
    client.send("Vous avez fait faillite!\n");
    while (game.getCurrentPlayer()->getBankAccount()->getMoney() < 0 and game.getCurrentPlayer()->getPlayerStatus() != PLAYER_STATUS::LOST){
        client.send("Seul trois optons s'offrent à vous: \n- /mortgage \n- /sell\n- /give-up.\n");
        client.receive(query);
        switch (query) {
            case GAME_QUERY_TYPE::MORTGAGE : case GAME_QUERY_TYPE::SELL_BUILDINGS : processGameQueryBeforeRoll(client, query); break;
            case GAME_QUERY_TYPE::GIVE_UP : processBankruptcyToPlayer(); game.getCurrentPlayer()->setPlayerStatus(PLAYER_STATUS::LOST); break;
            default: client.send("Cette commande n'est pas disponible.\n"); break;
        }
    }
    if (game.getCurrentPlayer()->getBankAccount()->getMoney() >= 0){
        game.getCurrentPlayer()->setPlayerStatus(PLAYER_STATUS::FREE);
    }
    if (PLAYER_STATUS::LOST != game.getCurrentPlayer()->getPlayerStatus()){
        client.send("Vous n'êtes plus en faillite! Continuez votre tour normalement.\n");
        game.getCurrentPlayer()->setPlayerStatus(PLAYER_STATUS::FREE);
    }
}

void GameServer::participateInAuction(ClientManager &client){
    client.send("Vous participez à l'enchère!");
    while (game.auctionInProgress() != 0) {}
}

void GameServer::clientAuctionLoop(ClientManager &client, LandCell* land_cell) {
    GAME_QUERY_TYPE query;
    sf::Packet packet;
    if (&client == game.getCurrentPlayer()->getClient()) {
        Player *winner = nullptr;
        int bid = 10;
        updateAllClients(
                "Une enchère a débuté! La propriété concernée est la suivante: " + land_cell->getLand()->getName() +
                "\nPour participer, tapez /participate. Pour ne pas participer, tapez /out.");
        if (game.getCurrentPlayer()->getPlayerStatus() != PLAYER_STATUS::LOST or game.getCurrentPlayer()->getBankruptingPlayer()->getPlayerStatus() != PLAYER_STATUS::LOST) {
            client.send(
                    "Attention! Comme vous êtes à l'origine de cette enchère, vous participez par défaut. \nVeuillez attendre 15 secondes que les autres joueurs rejoignent.");
        }
        game.startAuction();
        sleep(15);
        client.send("L'attente est terminée!");
        game.setAuctionProgress(2);
        while (winner == nullptr) {
            for (auto &player: *game.getPlayers()) {
                winner = game.identifyAuctionWinner();
                if (winner != nullptr) {
                    updateAllClients("Le joueur " + std::string(player.getClient()->getAccount()->getUsername()) +
                                     " a remporté l'enchère!");
                    player.acquireLand(land_cell->getLand());
                    player.pay(bid);
                    game.stopAuction();
                    break;
                }
                if (player.isInAuction() and (player.getPlayerStatus() != PLAYER_STATUS::LOST or player.getPlayerStatus() != PLAYER_STATUS::BANKRUPT)) {
                    player.getClient()->send(
                            "C'est à votre tour d'enchérir! \nLa plus haute enchère est actuellement à " +
                            std::to_string(bid) +
                            "e.\nTapez /bid [montant] pour enchérir et /out pour quitter l'enchère.\nToute commande invalide résultera en une exclusion de l'enchère.");

                    player.getClient()->receive(query, packet);
                    if (query == GAME_QUERY_TYPE::BID) {
                        std::string new_bid;
                        packet >> new_bid;
                        std::cout << "Recu " << new_bid << std::endl;
                        if (std::stoi(new_bid) <= bid or std::stoi(new_bid) > player.getBankAccount()->getMoney()) {
                            player.leaveAuction();
                            updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) +
                                             " est sorti(e) de l'enchère étant donné que sa proposition de prix était en dessous du minimum ou parce qu'iel n'avait pas les fonds suffisants.");
                        } else {
                            updateAllClients(
                                    std::string(player.getClient()->getAccount()->getUsername()) + " a surenchéri!");
                            bid = std::stoi(new_bid);
                        }
                    } else {
                        player.leaveAuction();
                        updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) +
                                         " est sorti(e) de l'enchère.");
                    }
                }
            }
        }
    }
}
        /*
        while()
                player.getClient()->send("C'est à votre tour d'enchérir! \nLa plus haute enchère est actuellement à " + std::to_string(bid) + "e.\nTapez /bid [montant] pour enchérir et /out pour quitter l'enchère.\nVous avez 10 secondes ou vous serez automatiquement exclu de l'enchère\nToute commande invalide résultera en une exclusion de l'enchère.");
                player.getClient()->receive(query, packet);
                if (query == GAME_QUERY_TYPE::BID) {
                    std::string new_bid;
                    packet >> new_bid;
                    std::cout << "Recu " << new_bid << std::endl;
                    if (std::stoi(new_bid) <= bid){
                        player.leaveAuction();
                        updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) + " est sorti(e) de l'enchère étant donné que sa proposition de prix était en dessous du minimum.");
                    }
                    else {
                        updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) + " a surenchéri!");
                        bid = std::stoi(new_bid);
                    }
                }
                else {
                    player.leaveAuction();
                    updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) + "est sorti(e) de l'enchère.");
                }
            }
        }
    }
         */

void GameServer::processStart(ClientManager &client) {
    if (this->game.isRunning())               { client.send("La partie est déjà en cours."); return; }
    if (!this->isClientAdmin(client))         { client.send("Vous n'êtes pas administrateur."); return; }
    if (this->game.getNumberOfPlayers() <= 1) { client.send("Vous êtes seul dans la partie, invitez un autre joueur pour lancer la partie."); return; }
    this->game.startGame();
    sendStartInfo();
    this->updateAllClients("La partie est lancée!");
}

void GameServer::processEndTurn(ClientManager &client) {
    Player* current = game.getCurrentPlayer();
    // Si le joueur n'a pas encore lancé les dés ou qu'il est en prison, on lui notifie simplement de lancé les dés
    if (!current->hasRolled() or current->isInJail()) {client.send("Vous devez jeter les dés avant de finir votre tour."); return;}
    // S'il a lancé les dés et qu'il n'est pas en prison alors c'est la fin de son tour, on reset le compteur de double et on change de joueur.
    this->game.getDice()->resetDoubleCounter();
    this->game.endCurrentTurn();

    // TODO : On envoie des infos pour le ncurse
    this->sendAllGameData();
}

void GameServer::processDiceRoll(ClientManager &client) {
    game.getCurrentPlayer()->rolled(true);
    std::string output = "";
    output += std::string(client.getAccount()->getUsername()) + " a jeté les dés et obtenu un " + std::to_string(game.rollDice()) + ".";
    if (game.rolledADouble()){
        output += "\nC'est un double! Iel pourra rejouer!";
    }
    updateAllClients(output);

    Player* current = game.getCurrentPlayer();
    

    current->move(game.getBoard()->getCellByIndex((current->getCurrentCell()->getPosition() + game.getDice()->getResults()) % BOARD_SIZE));
    updateAllClients(std::string(client.getAccount()->getUsername()) + " est arrivé sur la case " + std::to_string(game.getCurrentPlayer()->getCurrentCell()->getPosition())); //todo delete when affichage works

    if (game.getDice()->isDouble()) { game.getCurrentPlayer()->rolled(false);}
    if (game.getDice()->getDoubleCounter() == 2) {
        client.send("Vous allez en prison.");
        game.getCurrentPlayer()->goToJail(game.getBoard()->getCellByIndex(PRISON_INDEX));
    }
    else {
        game.getCurrentPlayer()->getCurrentCell()->action(game.getCurrentPlayer());
        if (game.getCurrentPlayer()->getPlayerStatus() == PLAYER_STATUS::BANKRUPT and game.getCurrentPlayer()->getBankruptingPlayer() !=
                                                                                      nullptr) {
            clientBankruptLoop(client);
        }
        if (game.getCurrentPlayer()->getPlayerStatus() != PLAYER_STATUS::LOST){
            LandCell *l;
            l = dynamic_cast<LandCell*>(game.getCurrentPlayer()->getCurrentCell());
            if (l != nullptr) {
                std::cout << "Pointer to owner: " << l->getLand()->getOwner() << std::endl;

                if (l->getLand()->getOwner() == nullptr){
                    updateAllClients("AUCTION STARTING");
                    clientAuctionLoop(client, l);
                }
                else{
                    std::cout << "Was already owned." << std::endl;
                    std::cout << "Owner is: " << std::string(l->getLand()->getOwner()->getClient()->getAccount()->getUsername()) << std::endl;
                }
            }
            else {
                std::cout << "Could not convert to LandCell" << std::endl;
            }
        }
    }
}

void GameServer::processDemortgageProperty(ClientManager &client) {
    GAME_QUERY_TYPE query;
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
    GAME_QUERY_TYPE query;
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
    while (query != GAME_QUERY_TYPE::SELECT){ //TODO check if no problem with undefined definition with while loop condition
        client.send("Pour choisir un joueur, utilisez /select nom d'utilisateur, pour annuler, tapez /leave.");
        client.receive(query, packet);
        packet >> name;
        exchange_player = getPlayerByUsername(name);
        if (exchange_player != nullptr or query == GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){
            break;
        }
        else {
            client.send("Nom de joueur invalide, veuillez réessayer.\n");
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
            if (land_cell->getLand()->getOwner() == exchange_player) {
                client.send("Propriété sélectionée!");
                client.send("Quel montant proposez-vous pour le rachat de cette propriété?\n Utilisez /select montant (ça doit être plus que 0).");
                client.receive(query, packet);
                packet >> name;
                while (true){
                    try {
                        proposed_amount = std::stoi(name);
                        if (proposed_amount <= game.getCurrentPlayer()->getBankAccount()->getMoney()){
                            break;
                        }
                        else {
                            client.send("Vous n'avez pas assez d'argent pour proposer ce montant.\n");
                        }
                    } catch (const std::invalid_argument& e) {
                        client.send("Invalid amount.\n");
                    }
                }
                if (proposeExchange(*game.getCurrentPlayer(), *exchange_player, land_cell->getLand(), proposed_amount)){
                    game.getCurrentPlayer()->acquireLand(land_cell->getLand());
                    game.getCurrentPlayer()->pay(proposed_amount);
                    exchange_player->receive(proposed_amount, std::string(game.getCurrentPlayer()->getClient()->getAccount()->getUsername()));
                    land_cell->getLand()->setOwner(game.getCurrentPlayer());
                    client.send("Votre proposition a été acceptée!.\n");
                }
                else{
                    client.send("Votre proposition a été refusée.\n");
                }
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
    std::string new_update = "GENERAL : " + update;
    for (auto client : clients){
        client->send(new_update);
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




#include "GameServer.hpp"
#include "../../Game/Board/Obtainable/Cells/LandCell.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../../utils/Configs.hpp"
#include "../../Game/Board/Obtainable/Cells/Land/Land.hpp"
#include "string.h"
#include "Timer.hpp"
#include "../../Game/Capitalist.hpp"
#include <string>

#include <SFML/Network.hpp>
#include <string>
#include <stdexcept>


void GameServer::clientLoop(ClientManager &client) {
	std::cout << client.getAccount()->getUsername() << " has join a game with code : " << this->code.getCode() << std::endl;
	while (this->active) {
		GAME_QUERY_TYPE query;
		sf::Packet packet;

        // if player is in jail
        if (game.getCurrentPlayer()->isInJail()){
            game.getCurrentPlayer()->getCurrentCell()->action(game.getCurrentPlayer());
        }
        else {
            clientBeforeRollLoop(client);
            // TODO after roll loop
    }
		game.receiveQuery(query, packet);
		if (query == GAME_QUERY_TYPE::LEAVE) { break; }
	}
	std::cout << client.getAccount()->getUsername() << " has left a game with code : " << this->code.getCode() << std::endl;
}

void GameServer::clientBeforeRollLoop(ClientManager &client) {
    while (true) {
        GAME_QUERY_TYPE query;
        sf::Packet packet;
        client.receive(query);
        if (&client == game.getCurrentPlayer()->getClient()){
            if (GAME_QUERY_TYPE::START == query) processStart(client);
            else if (game.isRunning()){
                if (&client == game.getCurrentPlayer()->getClient()){
                    if (processGameQueryBeforeRoll(client, query)){
                        break;
                    }
                }
                else {
                    client.send("Ce n'est pas encore votre tour.");
                }
            }
            else {
                client.send("La partie n'est pas encore lancée.");
            }
        }
        else {
            client.send("Cette action n'est pas permise étant donné que ça n'est pas votre tour.");
        }
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

bool GameServer::processGameQueryBeforeRoll(ClientManager &client, GAME_QUERY_TYPE query) {
    switch (query) {
        case GAME_QUERY_TYPE::END_TURN : processEndTurn(client); return false;
        case GAME_QUERY_TYPE::ROLL_DICE : processDiceRoll(client); return true; //only this line should return true, no other
        case GAME_QUERY_TYPE::MORTGAGE : processMortgageProperty(client); return false;
        case GAME_QUERY_TYPE::EXCHANGE : processExchange(client); return false;
        case GAME_QUERY_TYPE::BUILD : processBuildBuildings(client); return false;
        case GAME_QUERY_TYPE::SELL_BUILDINGS : processSellBuildings(client); return false;
        default: client.send("Cette commande n'est pas disponible."); return false;
    }
}

void GameServer::clientBankruptLoop(ClientManager &client) {
    GAME_QUERY_TYPE query;
    client.send("Vous avez fait faillite!\n");
    while (game.getCurrentPlayer()->getBankAccount()->getMoney() < 0){
        client.send("Seul trois optons s'offrent à vous: \n- /mortgage \n- /sell\n- /give-up.\n");
        client.receive(query);
        switch (query) {
            case GAME_QUERY_TYPE::MORTGAGE : case GAME_QUERY_TYPE::SELL_BUILDINGS : processGameQueryBeforeRoll(client, query); break;
            case GAME_QUERY_TYPE::GIVE_UP : processBankruptcyToPlayer(client); break;
            default: client.send("Cette commande n'est pas disponible.\n"); break;
        }
    }
    client.send("Vous n'êtes plus en faillite! Continuez votre tour normalement.\n");
    game.getCurrentPlayer()->setPlayerStatus(PLAYER_STATUS::FREE);
}

void GameServer::clientAuctionLoop(ClientManager &client, Land* land) {
    int bid = 10;
    GAME_QUERY_TYPE query;
    sf::Packet packet;
    updateAllClients("Une enchère de 30 secondes à débutée! La propriété concernée est la suivante: \n" + land->getName() + ". L'enchère débute à 10 euros!\nPour surenchérir, tapez /bid [montant].\n");

    game.startAuction();
    for (auto &player : *game.getPlayers()){
        Player* winner = game.identifyAuctionWinner();
        if (winner != nullptr)
        {
            updateAllClients("Le joueur " + std::string(player.getClient()->getAccount()->getUsername()) + " a remporté l'enchère!");
            player.acquireLand(land);
        }
        else if (player.isInAuction()){
            player.getClient()->send("C'est à votre tour d'enchérir! \nLa plus haute enchère est actuellement à " + std::to_string(bid) + "tapez /bid [montant] pour enchérir et /out pour quitter l'enchère.\nVous avez 10 secondes ou vous serez automoatiquement exclu de l'enchère\nToute commande invalide résultera en une exclusion de l'enchère.");
            //Timer t;
            //t.Start(11); //TODO implement timer
            client.receive(query, packet);
            if (query == GAME_QUERY_TYPE::BID) {
                std::string new_bid;
                packet >> new_bid;
                if (std::stoi(new_bid) <= bid){
                    player.leaveAuction();
                    updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) + "est sorti(e) de l'enchère.");
                }
                else {
                    updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) + " a surenchéri!");
                }
            }
            else {
                player.leaveAuction();
                updateAllClients(std::string(player.getClient()->getAccount()->getUsername()) + "est sorti(e) de l'enchère.");
            }
        }
    }
}

void GameServer::processStart(ClientManager &client) {
    if (!game.isRunning()){
        if (isClientAdmin(client)){
            if (game.getNumberOfPlayers() > 1){
                this->game.startGame();
                client.send("La partie est lancée!");
            }
            else {
                client.send("Vous êtes seul dans la partie, invitiez un autre joueur pour lancer la partie.");
            }
        }
        else {
            client.send("Vous n'êtes pas administateur.");
        }
    }
    else {
        client.send("La partie est déjà en cours.");
    }
}

void GameServer::processEndTurn(ClientManager &client) {
    if (game.getCurrentPlayer()->hasRolled() and !game.getCurrentPlayer()->isInJail()){
        game.endCurrentTurn();
        client.send("Votre tour est maintenant terminé.");
    }
    client.send("Vous devez jeter les dés avant de finir votre tour.");
}

void GameServer::processDiceRoll(ClientManager &client) {
    while (game.getDice()->getDoubleCounter() != 2){
        std::string output = "";
        output += std::string(client.getAccount()->getUsername()) + " rolled a " + std::to_string(game.rollDice()); //should technically have a method for this in capitalist, but flemme
        if (game.rolledADouble()){
            output += " and it's a double, he/she will play again!";
        }
        updateAllClients(output);
        game.getCurrentPlayer()->getClient()->send(output);
        game.getCurrentPlayer()->move(game.getBoard()->getCellByIndex((game.getCurrentPlayer()->getCurrentCell()->getPosition() + game.getDice()->getResults()) % BOARD_SIZE));

        game.getCurrentPlayer()->getCurrentCell()->action(game.getCurrentPlayer());
        if (game.getCurrentPlayer()->getPlayerStatus() == PLAYER_STATUS::BANKRUPT and game.getCurrentPlayer()->getBankruptingPlayer() !=
                                                                                              nullptr){
            clientBankruptLoop(client);
        }
        Land *l = dynamic_cast<Land*>(game.getCurrentPlayer()->getCurrentCell());
        if (l != nullptr) {
            if (l->getOwner() == nullptr){
                clientAuctionLoop(client, l);
            }
        }
        if (!game.getDice()->isDouble()) { break; }
    }
    game.getCurrentPlayer()->rolled(true);
    if (game.getDice()->getDoubleCounter() == 2) {
        game.getCurrentPlayer()->goToJail(game.getBoard()->getCellByIndex(PRISON_INDEX));
    }
}

void GameServer::processMortgageProperty(ClientManager &client) { //for now, only works for bankruptcy if bankrupt player is the player whose turn it is.
    GAME_QUERY_TYPE query;
    sf::Packet packet;
    std::string name;
    client.send("Veuillez selectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des batiments.\n");
    while (query != GAME_QUERY_TYPE::LEAVE_SELECTION_MODE){ //TODO check if no problem with undefined definition with while loop condition
        client.receive(query, packet); //todo check if problem if no package sent problem
        packet >> name;
        if (query == GAME_QUERY_TYPE::SELECT){
            LandCell* land_cell = game.getCellByName(name);
            if (land_cell != nullptr and land_cell->getLand()->getOwner() == game.getCurrentPlayer()){
                land_cell->getLand()->mortgage(game.getCurrentPlayer());
            }
            else {
                client.send("Cette propriété n'existe pas ou elle ne vous appartient pas.\n");
            }
        }
        else {
            client.send("Veuillez selectionner la propriété à hypothéquer en utilisant /select [nom de la propriété].\nTapez /leave pour quitter le mode de selection des propriétés.\n");
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
            break;
        }
        packet >> name;
        Land* land = getLandByName(name);
        Property* p = dynamic_cast<Property*>(land);
        if (p != nullptr and p->build(game.getCurrentPlayer())){
            client.send("Vous avez construit un batiment.\n");
        }
        else {
            client.send("Building failed.\n");
        }
    }
}

void GameServer::processSellBuildings(ClientManager &client) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string name;
    client.send(
            "Selectionnez une propriété sur laquelle vendre un batiment avec la commande /select nom de la propriété.\n");
    while (true) {
        client.send("Pour quitter le mode de sélection de propriétés. Tapez /leave.\n");
        client.receive(query, packet);
        if (query == GAME_QUERY_TYPE::LEAVE_SELECTION_MODE) {
            break;
        }
        packet >> name;
        Land *land = getLandByName(name);
        Property *p = dynamic_cast<Property *>(land);
        if (p != nullptr and p->sellBuilding(game.getCurrentPlayer())) {
            client.send("Vous avez construit un batiment.\n");
        } else {
            client.send("Building failed.\n");
        }
    }
}

bool GameServer::proposeExchange(Player &proposing_player, Player &proposed_to_player, Land *land, int amount) {
    GAME_QUERY_TYPE query = GAME_QUERY_TYPE::NONE;
    sf::Packet packet;
    std::string response;
    std::string comm_string = "";
    comm_string += (std::string(proposing_player.getClient()->getAccount()->getUsername()) + "vous propose " + std::to_string(amount) + " pour votre possesion nommée " + land->getName());
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

void GameServer::processBankruptcyToPlayer(ClientManager &client){
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
    Land* land = land_cell->getLand();
    return land;
}

void GameServer::updateAllClients(std::string update) {
    for (auto client : clients){
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

void GameServer::addPlayer(ClientManager &client) {this->game.addPlayer(client);}

bool GameServer::isClientAdmin(ClientManager &client) {return (game.getPlayerByClient(client)->isAdmin());}

bool GameServer::isCode(int other) const { return code.getCode() == other; }




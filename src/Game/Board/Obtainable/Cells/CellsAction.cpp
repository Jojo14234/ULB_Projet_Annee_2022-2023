#include "../../../Player/Player.hpp"
#include "DrawableCardCell.hpp"
#include "GoJailCell.hpp"
#include "JailCell.hpp"
#include "LandCell.hpp"
#include "ParkingCell.hpp"
#include "TaxCell.hpp"
#include "../../../../Server/Game/GameServer.hpp"

void DrawableCardCell::action(Player* player) {
    Card* drawn_card = deck->drawACard();
    player->getClient()->send("Vous avez pioché cette carte : \n\t" + drawn_card->getDescription() + "\n");
    drawn_card->action(player);
} 

void GoJailCell::action(Player* player) {
    player->goToJail(jail);
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_SEND_TO_PRISON, player->getUsername());
}

void LandCell::action(Player* player) {
    // Msg
    std::string str = std::to_string(player->getClient()->getGameServer()->getCurrentPlayerIndex()) + ":";;
    str += land->getName() + ":";
    str += std::to_string(player->getBankAccount()->getMoney());
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE, str);


    switch (land->getStatus()) {
        case::LAND_STATUS::FREE : this->buy(player); break;
        case::LAND_STATUS::PAID : this->pay(player); break;
        case::LAND_STATUS::HYPOTEK : this->mortgage(player); break;
        default: break;
    }
}

void LandCell::buy(Player *player) {
    while ( true ) {

        // MESSAGE + OUTPUT
        GAME_QUERY_TYPE query;
        sf::Packet packet;
        player->getClient()->send("Acheter " + land->getName() + " pour " + std::to_string(land->getPurchasePrice())+"$ ?");
        player->getClient()->send("/yes ou /no");
        player->getClient()->send("Si vous ne l'achetez pas, des encheres debuteront");
        player->getClient()->receive(query);

        if ( query == GAME_QUERY_TYPE::YES ) {
            // Si il peut pas payer
            if (!player->pay(this->land->getPurchasePrice())) { continue; }
            // Obtention de la carte
            player->acquireLand(this->getLand());

            // Message
            std::string str;
            str = std::to_string(player->getIndex()) + ":";
            str += land->getName() + ":";
            str += std::to_string(player->getMoney());

            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_BOUGHT, str);
            break;
        }
        if ( query == GAME_QUERY_TYPE::NO ) {
            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_DIDNT_BUY, player->getUsername());
            break;
        }
    }
}

void LandCell::pay(Player *player) {
    if (player == this->getOwner()) { player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL, player->getUsername());}

    if (!player->pay(land->getRentPrice(), true)) { player->setPlayerToRefund(this->getOwner()); }

    this->getOwner()->receive(land->getRentPrice(), player->getUsername());

    std::string str = std::to_string(land->getRentPrice()) + ":";
    str += std::to_string(player->getIndex()) + ":";
    str += std::to_string(player->getMoney()) + ":";
    str += std::to_string(this->land->getOwner()->getIndex()) + ":";
    str += std::to_string(this->land->getOwner()->getMoney());
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_PAID_PLAYER, str);

}

void LandCell::mortgage(Player *player) {
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL, player->getUsername() + ":" + land->getOwner()->getUsername());

}

void TaxCell::action(Player* player) {
    player->pay(tax_price, true);

    std::string str = name + ":";
    str += std::to_string(tax_price) + ":";
    str += std::to_string(player->getIndex()) + ":";
    str += std::to_string(player->getMoney());

    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL, str); 
}

void ParkingCell::action(Player *player) {
    std::string str = player->getUsername() + ":" +  this->getName() + ":" + std::to_string(player->getMoney());
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE, str);
    player->getClient()->send("Incroyable! le parc gratuit! il ne se passe rien."); 
}

void JailCell::action(Player *player) {
    if (player->isInJail()) {    // y'avais un !
        player->getClient()->send("Vous êtes en prison: /roll, /usecard ou /pay.");
        player->getClient()->send("| Vous possedez " + std::to_string(player->hasGOOJCards()) + " cartes pour sortir de prison.");

        GAME_QUERY_TYPE query;
        sf::Packet packet;

        // receive from client
        player->getClient()->receive(query, packet);

        bool end_round = false;

        while (not end_round) {
            switch (query) {
                case GAME_QUERY_TYPE::PAY: {
                    end_round = outWithMoney(player, false);
                    break;
                }
                case GAME_QUERY_TYPE::USEGOOJCARD: {
                    end_round = outWithCard(player);
                    break;
                }
                case GAME_QUERY_TYPE::ROLL_DICE: {
                    Dice dice = Dice();
                    end_round = outWithDice(player, dice);
                    // if (free) dice.getResult play
                    break;
                }
                default: break;
            }
        }
    }
    else {
        std::string str = player->getUsername() + ":" +  this->getName() + ":" + std::to_string(player->getMoney());
        player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE, str);
        player->getClient()->send("Vous visitez la prison, il ne vous arrive rien.");  
    }
    //envoyer demande de choix au client (reception, receive)
}

bool JailCell::outWithMoney(Player *player, bool forced) {
    if (player->pay(50, forced)) {   //si n'arrive pas a payer
        player->setExitJail();
        player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_GO_OUT_PRISON, player->getUsername());
        return true;
    } else if (!forced) {
        return false;   //s'il a fait le choix de payer mais pas assez d'argent
        //continue à choisir un moyen de sortir de prison
        //(otherwise c'est bankrupt)
    }
    else return true;    //si choix de payer mais pas assez d'argent
    }

    bool JailCell::outWithCard(Player *player) {
        if (player->hasGOOJCards()) {
            player->setExitJail();
            player->looseGOOJCard();
            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_GO_OUT_PRISON, player->getUsername());
            return true;
        } else {   //echange demandé depuis prison, mettre à jour le player et sortie de boucle (boucle echange lancé dans game server)
            player->setExchangeFromJail();  //achete ou non une carte
            return false;   //retour à la boucle de choix, si le joueur a acheter une carte, peut l'utiliser en choississant l'option GOOJ
        }

    }

    bool JailCell::outWithDice(Player *player, Dice dice) { //test les dés et apres fin du tour
        player->addRollInPrison();
        if (dice.isDouble()) {
            player->setExitJail();
            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_GO_OUT_PRISON, player->getUsername());
            //penser à une méthode pour que le joueur joue (si pas le temps, juste freed et tour du joueur suivantS)
            return true;
        } else if (player->getRollsInPrison() == 3) {
            return this->outWithMoney(player, true);
        } else return true;    //si pas de double mais que pas le 3e lancée, fin du tour du joueur

    }
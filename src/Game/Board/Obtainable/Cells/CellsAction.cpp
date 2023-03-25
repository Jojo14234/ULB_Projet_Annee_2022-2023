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
    // Message concernant l'achat ou non d'une propriété
    std::string str = "La propriété est libre, voulez-vous l'acheter pour [" + std::to_string(land->getPurchasePrice())+"e] ?";
    str += "\n - Achetez la propriété ( /yes )";
    str += "\n - Ne pas achetez la propriété ( /no )";
    str += "\n Dans le cas où vous n'achèteriez pas la propriété,";
    str += "\n elle sera mise au enchère pour tout le monde !\n";

    while ( true ) {

        // MESSAGE + OUTPUT
        GAME_QUERY_TYPE query;
        sf::Packet packet;
        player->getClient()->send(str);
        player->getClient()->receive(query);

        if ( query == GAME_QUERY_TYPE::YES ) {
            // Si il peut pas payer
            if (!player->pay(this->land->getPurchasePrice())) { continue; }
            // Obtention de la carte
            player->acquireLand(this->getLand());

            // Message
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
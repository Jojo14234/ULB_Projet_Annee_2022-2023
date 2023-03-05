#include "MoneyCard.hpp"
#include "../../../Player.hpp"
#include "../../../../Server/ClientManager/ClientManager.hpp"

void MoneyCard::action(Player* player) {
    if (receive) {
        player->receive(amount, "Bank");
        player->getClient()->send("Vous recevez "+std::to_string(amount)+"$");
    }
    else {
        if (amount != 0) { player->pay(amount, true); player->getClient()->send("Vous payez "+std::to_string(amount));}
        else {
            std::vector<Property*> properties = player->getAllProperties();
            for ( auto &elem : properties ){
                if (elem->getIntLevel() <= 4) { player->pay(amount_house, true); }
                else if (elem->getIntLevel() == 5) { player->pay(amount_hotel, true); }
            }
        }
    }
}								//modif argent du joueur selon receive et amount
                                //si carte spécial annif, prendre argent des autres joueurs
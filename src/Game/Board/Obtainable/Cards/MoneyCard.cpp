#include "MoneyCard.hpp"
#include "../../../Player/Player.hpp"
#include "../../../../Server/ClientManager/ClientManager.hpp"
#include "../Cells/Land/Property.hpp"
#include "../../../../Server/Game/GameServer.hpp"


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
                if (elem->getIntLevel() <= 4) { player->pay(amount_house * elem->getIntLevel() , true); }
                else if (elem->getIntLevel() == 5) { player->pay(amount_hotel, true); }
            }
        }
    }
}								//modif argent du joueur selon receive et amount
                                //si carte spécial annif, prendre argent des autres joueurs

void FromOtherMoneyCard::action(Player* player) {
        std::vector<Player>* players = player->getClient()->getGameServer()->getGame()->getPlayers();
        for (auto &other_player : *players) {
            if (player != &other_player) {  //opti calcul nombre de gens et somme total
                other_player.pay(amount, true);
                player->receive(amount, other_player.getUsername());        //MoneyCard::action() ?
            }
        }
}

void ChoiceMoneyCard::action(Player* player) {
        std::string msg = "amende: /select amende | carte: /select carte";
        player->getClient()->sendQueryMsg(msg, QUERY::MESSAGE);

        std::string answer;
        GAME_QUERY_TYPE query;
        sf::Packet packet;
        player->getClient()->receive(query, packet);

        packet >> answer;

        if (answer == "amende") {
            player->pay(this->amount, true);    //MoneyCard::action() ?
        }
        else if (answer == "carte") {
            CardDeck* deck = player->getClient()->getGameServer()->getDeck(this->deck_name);
            Card* drawn_card = deck->drawACard();
            player->getClient()->send("Vous avez pioché cette carte : \n\t" + drawn_card->getDescription() + "\n");
            drawn_card->action(player);
        }
        //faire une boucle car possible qu'il disent n'imp (break si boucle while) !!

}
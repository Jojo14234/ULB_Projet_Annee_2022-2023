
#include "MoneyCard.hpp"
#include "../../../../Server/Game/GameServer.hpp"



int MoneyCard2::getAmount() { return this->amount; }

void MoneyCard2::setAmount(int new_amount) { this->amount = new_amount; }

void MoneyCard2::action(Player *player) {
    std::string str = std::to_string(player->getIndex()) + ":" + std::to_string(amount) + ":";
    if (this->amount > 0) {
        player->receive(std::abs(this->amount), "la banque");
        str += std::to_string(player->getMoney());
        player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_WON_MONEY, str);
    }
    else if (this->amount < 0) {
        player->pay(std::abs(this->amount), true);
        str += std::to_string(player->getMoney());
        player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_LOSE_MONEY, str);
    }
    
}

void HouseHotelMoneyCard::action(Player *player) {
    int house = 0;
    int hotel = 0;

    for (auto property : player->getAllProperties()) {
        if ( property->getLevel() == PROPERTY_LEVEL::HOTEL ) { hotel++; }
        else { house += property->getIntLevel(); }
    }
    int new_amount = (house * this->house_price + hotel * this->hotel_price) * -1;
    this->setAmount(new_amount);
    MoneyCard2::action(player);
}

void ChoiceMoneyCard::action(Player* player) {

    while ( true ) {
        GAME_QUERY_TYPE query;
        player->getClient()->sendQueryMsg("", QUERY::CHOICE_MONEY_CARD);
        player->getClient()->receive(query);

        if ( query == GAME_QUERY_TYPE::PAY ) { MoneyCard2::action(player); break; }

        if ( query == GAME_QUERY_TYPE::CARD ) {
            CardDeck* deck = player->getClient()->getGameServer()->getDeck(this->deck_name);
            Card* drawn_card = deck->drawACard();
            player->getClient()->sendQueryMsg(drawn_card->getDescription(), QUERY::INFOS_CARD_DESCRIPTION);
            drawn_card->action(player);
            break;
        }
    }
}

void FromOtherMoneyCard::action(Player* player) {
    std::vector<Player>* players = player->getClient()->getGameServer()->getGame()->getPlayers();
    int new_amount = 0;
    for (auto &other_player : *players) {
        if (player != &other_player) {
            other_player.pay(this->getAmount(), true);
            new_amount += this->getAmount();
            //Query Spéciale qui envoie toutes les infos à jours 
        }
    }
    this->setAmount(new_amount);
    MoneyCard2::action(player);
}


#ifndef _GAME_MONEY_CARD_HPP
#define _GAME_MONEY_CARD_HPP

#include <string>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

#include "Card.hpp"
#include "../../../../Server/ClientManager/QUERY.hpp"


class Player;

class MoneyCard: public Card {

private:
	//"Versez pour chaque maison 25$. Versez pour chaque hôtel 80$."
	int amount_house;
	int amount_hotel;
	bool receive; //1 true, reçoit l'amount, sinon retire l'amount perd argent

protected:
	int amount;	//reflechir à garder montant negatif si retire argent ou pas

public:
	
	explicit MoneyCard(Json::Value &info):Card{info}, amount{info["amount"].asInt()}, amount_house{info["amount_house"].asInt()}, amount_hotel{info["amount_hotel"].asInt()}, receive(info["receive"].asBool()) {}

	void action(Player* player) override ;

};

class FromOtherMoneyCard: public MoneyCard {
public:
	FromOtherMoneyCard() {}

	void action(Player* player) {
		
	}

};

class ChoiceMoneyCard: public MoneyCard {
private:
	std::string deck_name;

public:
	ChoiceMoneyCard() {}

	void action(Player* player) {
		std::string msg = "amende: /select amende | carte: /select carte";
		player->getClient()->sendQueryMsg(msg, QUERY::SELECT);

		std::string answer;
		GAME_QUERY_TYPE query;
        sf::Packet packet;
        player->getClient()->receive(query, packet);

        packet >> answer;

        if (answer == "amende") {
        	player->forcedPay(this->amount);
        }
        else if (answer == "carte") {
        	CardDeck* deck = player->getClient()->getGameServer()->getDeck(this->deck_name);
        	Card* drawn_card = deck->drawACard();
    		player->getClient()->send("Vous avez pioché cette carte : \n\t" + drawn_card->getDescription() + "\n");
    		drawn_card->action(player);
        }
        //faire une boucle car possible qu'il disent n'imp (break si boucle while)

	}

};


#endif

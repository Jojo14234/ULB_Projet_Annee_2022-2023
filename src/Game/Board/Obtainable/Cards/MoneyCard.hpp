#ifndef _GAME_MONEY_CARD_HPP
#define _GAME_MONEY_CARD_HPP

#include <string>
#include <json/json.h>

#include "Card.hpp"


class Player;

class MoneyCard: public Card {

private:
	int amount;	//reflechir à garder montant negatif si retire argent ou pas

	//"Versez pour chaque maison 25$. Versez pour chaque hôtel 80$."
	int amount_house;
	int amount_hotel;
	bool receive; //1 true, reçoit l'amount, sinon retire l'amount perd argent

public:
	
	explicit MoneyCard(Json::Value &info):Card{info}, amount{info["amount"].asInt()}, amount_house{info["amount_house"].asInt()}, amount_hotel{info["amount_hotel"].asInt()}, receive(info["receive"].asBool()) {}

	void action(Player* player) {
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
	};								//modif argent du joueur selon receive et amount
									//si carte spécial annif, prendre argent des autres joueurs

};

#endif

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
protected:
	int amount;	//reflechir à garder montant negatif si retire argent ou pas

private:
	//"Versez pour chaque maison 25$. Versez pour chaque hôtel 80$."
	int amount_house;
	int amount_hotel;
	bool receive; //1 true, reçoit l'amount, sinon retire l'amount perd argent

public:
	
	explicit MoneyCard(Json::Value &info):Card{info}, amount{info["amount"].asInt()}, amount_house{info["amount_house"].asInt()}, amount_hotel{info["amount_hotel"].asInt()}, receive(info["receive"].asBool()) {}
	MoneyCard(std::string descript, int amount, bool receive): Card{descript}, amount{amount}, amount_house{0}, amount_hotel{0}, receive{receive} {}

	void action(Player* player) override ;

};

class FromOtherMoneyCard: public MoneyCard {
public:
	FromOtherMoneyCard(std::string descript, int amount, bool receive): MoneyCard{descript, amount, receive} {}

	void action(Player* player);

};

class ChoiceMoneyCard: public MoneyCard {
private:
	std::string deck_name;

public:
	ChoiceMoneyCard(std::string descript, int amount, bool receive, std::string deckname): MoneyCard{descript, amount, receive}, deck_name{deckname} {}

	void action(Player* player);

};


#endif

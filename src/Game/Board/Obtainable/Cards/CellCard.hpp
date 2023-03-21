#ifndef _GAME_CARD_CELL_HPP
#define _GAME_CARD_CELL_HPP

#include <string>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#endif

#ifdef __APPLE__
#include <json/json.h>
#endif

#include "Card.hpp"


class Player;

class CellCard: public Card {

private:

	int dest;
	bool gain_money;	//"Si vous passez par la case départ, recevez 200$"

public:

	explicit CellCard(Json::Value &info):Card{info}, dest{info["dest"].asInt()}, gain_money{info["money"].asBool()} {}

	CellCard(std::string descript, int dest, bool gain_money): Card{descript}, dest{dest}, gain_money{gain_money} {}

	void action(Player* player) override ;

	void setDest(int new_dest) {this->dest = new_dest;}


											//déplace le joueur à cells[dest]
											// if gain money, check si position du joueur>dest (passe par case départ) pour argent

};

class MoveBackCellCard : public CellCard {
private:
	int step_back;

public:
	MoveBackCellCard(std::string descript, bool gain_money, int back): CellCard{descript, 0, gain_money}, step_back{abs(back)} {}

	void action(Player* player) override;

};

class NearestCellCard : public CellCard {
private:
	std::array<int, 4> near_pos;

	int searchMinIdx(std::array<int, 4> dest_pos);

	std::array<int, 4> makeDestArray(int current_pos);

public:
	NearestCellCard(std::string descript, bool gain_money, std::array<int, 4> dest_array): CellCard{descript, 0, gain_money}, near_pos{dest_array} { }	//passer l'array ici ou faire ici

	void action(Player* player) override;
};

#endif

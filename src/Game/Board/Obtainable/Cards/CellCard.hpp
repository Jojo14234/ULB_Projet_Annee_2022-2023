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

	explicit CellCard(Json::Value &info):Card{info}, dest{info["dest"].asInt()}, gain_money{info["dest"].asBool()} {}

	void action(Player* player) override ;

	void setDest(int new_dest) {this->dest = new_dest;}


											//déplace le joueur à cells[dest]
											// if gain money, check si position du joueur>dest (passe par case départ) pour argent

};

class MoveBackCellCard : public CellCard {
private:
	int back;

public:
	MoveBackCell(std::string descript, int dest, bool gain_money) CellCard{} { }

	void action(Player* player){
		int current_pos = player.getCurrentCell().getPosition();
		this->setDest(current_pos+back);
		this->CellCard::action();
	};

};

class NearestCellCard : public CellCard {
private:
	std::array<int, 4> near_pos;

	int searchMinIdx(std::array<int, 4> dest_pos) {
		int min_idx = 0;
		for (int i=0; i<4, i++){
			if (dest_pos[i] > 0) {
				if (dest_pos[i] < dest_pos[min_idx]) {
					min_idx = i;
				}
			}
		}
		return min_idx;
	};

	std::array<int, 4> makeDestArray(int current_pos) {
		std::array<int, 4> dest_pos;
		for (int i=0; i<4; i++){
			dest_pos[i] = this->near_pos[i] - current_pos;
		}
		return dest_pos;
	};

public:
	NearestCellCard() CellCard{} { }

	void action(Player* player){
		int current_pos = player.getCurrentCell().getPosition();
		std::array<int, 4> dest_pos = this->makeDestArray(current_pos);
		int nearest_dest = this->searchMinIdx(dest_pos);
		this->setDest(nearest_dest);
		this->CellCard::action();
	};
};

#endif

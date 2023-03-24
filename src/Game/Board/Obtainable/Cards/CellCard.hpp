#ifndef _GAME_CARD_CELL_HPP
#define _GAME_CARD_CELL_HPP

#include <array>
#include <string>

#include "Card.hpp"


class Player;

class CellCard: public Card {

private:

	int destination;
	bool receive_money;

public:

	CellCard(std::string description, int destination, bool receive_money)
            :Card{description}, destination{destination}, receive_money{receive_money} {}

	void action(Player* player) override ;

	void setDest(int new_dest) {this->destination = new_dest;}

};

class NearestCellCard : public CellCard {

private:

	std::array<int, 4> stations;
    int findNearestStation(int current_pos);

public:

	NearestCellCard(std::string description, bool receive_money, std::array<int, 4> stations)
            :CellCard{description, 0, receive_money}, stations{stations} {}

	void action(Player* player) override;

};

#endif

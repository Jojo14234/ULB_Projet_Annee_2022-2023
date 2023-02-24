//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_BOARD_HPP
#define INFO_F209_GR5_2022_BOARD_HPP

#include "Card.hpp"
#include "Cell.hpp"

#include <array>
#include <memory>


class Board {
private:
	CardDeck community_deck;
	CardDeck lucky_deck;
	array<std::shared_ptr<Cell>, 40> cells;

	void initAllCells();
	void initAllDecks();

public:
	Board();
};


#endif //INFO_F209_GR5_2022_BOARD_HPP

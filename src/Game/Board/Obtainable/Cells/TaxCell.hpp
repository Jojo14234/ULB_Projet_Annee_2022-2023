#ifndef _GAME_TAX_CELL_HPP
#define _GAME_TAX_CELL_HPP

#include <string>

#include "Cell.hpp"


class Player;


class TaxCell: public Cell{
    
	int tax_price;

	void takeMoney();

public:
    
	TaxCell(int pos, int amount): Cell{pos}, tax_price{amount} {}
    
	void action(Player* player);

};

#endif

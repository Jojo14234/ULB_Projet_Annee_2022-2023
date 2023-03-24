#ifndef _GAME_TAX_CELL_HPP
#define _GAME_TAX_CELL_HPP

#include <string>
#include "Cell.hpp"


class Player;

class TaxCell: public Cell {
    
	int tax_price;
	std::string name;

public:
    
	TaxCell(int pos, int tax_price, std::string &name) : Cell{pos, name}, tax_price{tax_price}, name{name} {}
    
	void action(Player* player) override ;

};

#endif

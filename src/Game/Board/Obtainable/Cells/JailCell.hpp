#ifndef _GAME_JAIL_CELL_HPP
#define _GAME_JAIL_CELL_HPP

#include <string>

#include "Cell.hpp"


class Player;

class JailCell: public Cell{
    
	void outWithMoney();
    
	void outWIthCard();
    
	void outWithDice();
    
	void out();

public:

	JailCell(int pos);
    
	void action(Player* player);

};

#endif

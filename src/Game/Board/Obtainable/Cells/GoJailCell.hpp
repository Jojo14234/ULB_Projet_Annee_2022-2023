#ifndef _GAME_GO_JAIL_CELL_HPP
#define _GAME_GO_JAIL_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "JailCell.hpp"


class Player;

class GoJailCell: public Cell{

	JailCell* jail;

	void goToJail();

public: 
    
	GoJailCell(int pos);
    
	void action(Player* player);

};

#endif

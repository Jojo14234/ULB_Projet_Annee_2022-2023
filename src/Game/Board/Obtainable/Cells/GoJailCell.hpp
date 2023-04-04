#ifndef _GAME_GO_JAIL_CELL_HPP
#define _GAME_GO_JAIL_CELL_HPP

#include <string>
#include <memory>

#include "Cell.hpp"
#include "JailCell.hpp"


class Player;

class GoJailCell: public Cell{

	JailCell* jail;

public: 
    
	GoJailCell(int pos, JailCell* jail, std::string &name) : Cell{pos, name}, jail{jail} {}
    
	void action(Player* player) override ;

};

#endif

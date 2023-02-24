#ifndef _GAME_PROPERTY_CELL_HPP
#define _GAME_PROPERTY_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "../../Player.hpp"
#include "Property.hpp"


class PropertyCell : public Cell {

    Property property;
    
	bool isOwner();

public: 

	PropertyCell(int pos, Property prop): Cell{pos}, property{prop} {}
    
	void action(Player* player);

};

#endif

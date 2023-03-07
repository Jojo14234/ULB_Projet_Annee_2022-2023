#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>
#include <memory>

#include "Cell.hpp"
#include "Land/Land.hpp"


class PLayer;

class LandCell : public Cell {

    std::shared_ptr<Land> land;
    
	bool isOwner(Player* player) {return land->getOwner()==player;}

public: 

	LandCell(int pos, std::shared_ptr<Land> land): Cell{pos}, land{land} {}
    
	//~LandCell() { delete land; }

	void action(Player* player);

    Land* getLand(){return land.get(); }

};

#endif

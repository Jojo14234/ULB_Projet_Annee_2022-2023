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

	LandCell(int pos, std::shared_ptr<Land> land, std::string name="Undefined"): Cell{pos, name}, land{land} {}
    
	//~LandCell() { delete land; }

	void action(Player* player) override ;

    Land* getLand(){return land.get(); }

};

#endif

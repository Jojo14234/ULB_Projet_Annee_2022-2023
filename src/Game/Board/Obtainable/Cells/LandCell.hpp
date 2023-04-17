#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>
#include <memory>

#include "Cell.hpp"
#include "Land/Land.hpp"
#include "../../../Player/Player.hpp"


class LandCell : public Cell {

    std::shared_ptr<Land> land;
    
	bool isOwner(Player* player) { return land->getOwner()==player; }


public: 

	LandCell(int pos, std::shared_ptr<Land> land, std::string name="Undefined"): Cell{pos, name}, land{land} {}

	void action(Player* player) override;

    void buy(Player* player);
    void pay(Player* player);
    void mortgage(Player* player);

    Land* getLand() const { return this->land.get(); }
    Player* getOwner() const { return this->land->getOwner(); }

    bool isLandCell() override { return true; } //to avoid having to dynamic cast all Cells to check if it's a LandCell

};

#endif

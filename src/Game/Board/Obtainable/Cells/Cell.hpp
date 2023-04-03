#ifndef _GAME_CELL_HPP
#define _GAME_CELL_HPP

#include "../Obtainable.hpp"
#include "Land/Land.hpp"
#include "../../../Player/Player.hpp"
#include "../../../../Server/ClientManager/ClientManager.hpp"
#include "../../../../utils/Configs.hpp"


class Cell: public Obtainable {

    int position;
    std::string name;

public:

    Cell(int pos, std::string name = "Undefined"): position{pos}, name{name} {}
    
	virtual ~Cell()=default;

	virtual void action(Player* player) override =0;

    int getPosition() const { return position; }
    std::string getName() { return name; }

    bool isLandCell() { return false; }
};

#endif

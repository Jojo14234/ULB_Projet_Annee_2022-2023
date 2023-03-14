#ifndef _GAME_CELL_HPP
#define _GAME_CELL_HPP

#include "../Obtainable.hpp"
#include "Land/Land.hpp"
#include "../../../Player/Player.hpp"
#include "../../../../Server/ClientManager/ClientManager.hpp"
#include "../../../../utils/Configs.hpp"


class Cell: public Obtainable {

    int position;

public:

	Cell(int pos): position{pos} {}
    
	virtual ~Cell()=default;

	virtual void action(Player* player) override =0;

    int getPosition() { return position; }

};

#endif

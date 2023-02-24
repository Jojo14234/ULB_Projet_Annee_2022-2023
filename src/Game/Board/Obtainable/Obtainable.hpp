#ifndef _GAME_OBTAINABLE_HPP
#define _GAME_OBTAINABLE_HPP

#include <string>

#include "../../Player.hpp"


class Obtainable {

protected:

	Player* actual_player;

public:
	
	virtual ~Obtainable();

	virtual void action(Player* player)=0;

};

#endif

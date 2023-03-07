#ifndef _GAME_OBTAINABLE_HPP
#define _GAME_OBTAINABLE_HPP

#include <string>


class Player;

class Obtainable {

protected:

	Player* actual_player;

public:

	virtual ~Obtainable()=default;

	virtual void action(Player* player)=0;

};

#endif

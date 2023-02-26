#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

class Station : Land{
private:
	int getRentPrice(); // dépend de owner et le nombre de gare qu'il a


public:
	void action(Player* player);
}

#endif
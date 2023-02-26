#ifndef _GAME_PROPERTY_HPP
#define _GAME_PROPERTY_HPP

class Company : Land{
private:
	int getRentPrice(); //dé  jeter les dés x5 ou x12 selon le owner possession
	

public:
	void action(Player* player);
}

#endif
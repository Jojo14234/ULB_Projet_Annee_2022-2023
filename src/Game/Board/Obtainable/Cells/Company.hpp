#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"
#include "../../../../Game/Dice.hpp"

class Player;

class Company : public Land {

	int getRentPrice(){
		unsigned int nbr_of_company = this->owner.getNumberOfStations();
		int dice_res = Dice().roll();
		switch (nbr_of_company) {
			case 1:
				return dice_res*5;
				break;
			case 2:
				return dice_res*12;
				break;
		}
	}; 
	//dé  jeter les dés x5 ou x12 selon le owner possession
	
public:

	void action(Player* player);

};

#endif
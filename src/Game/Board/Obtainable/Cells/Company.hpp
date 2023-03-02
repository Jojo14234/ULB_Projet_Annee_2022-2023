#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"
#include "../../../../Game/Dice.hpp"

class Player;

class Company : public Land {

	int getRentPrice(){
		unsigned int nbr_of_company = this->owner.getNumberOfCompanies();
		int dice_res = Dice().roll();
		switch (nbr_of_company) {
			case 1:
				return dice_res*5;
			case 2:
				return dice_res*12;

		}
	}; 
	//dé  jeter les dés x5 ou x12 selon le owner possession
	
public:

	void action(Player* player);

	void playerPurchase(Player* player) {
		super->playerPurchase();
		//update dans les vecteurs de player
	}

};

#endif
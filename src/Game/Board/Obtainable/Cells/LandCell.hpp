#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "Land.hpp"


class PLayer;

class LandCell : public Cell {

    Land land;
    
	bool isOwner(Player* player) {return land->getOwner()==player;};

public: 

	LandCell(int pos, Land land): Cell{pos}, Land{land} {}
    
	void action(Player* player) {
		player->getClient()->send("Vous êtes tomber sur la propriéte"+land.getName());
		if (land.getOwner() == nullptr) {
			player->getClient()->send("La propriété est libre, voulez-vous l'acheter pour "+std::toString(land.getPurchasePrice())+"$");
			//TO DO reception paquet
			//si achete: 
			land.playerPurchase(player);
			//si ne peut pas ou n'achete pas -> enchere


		}
		else if (not this->isOwner(player) && land.getOwner() != nullptr) {
			rent = land.getRentPrice();
			player->pay(rent, true);
			player->getClient()->send("Qui appartient à un autre joueur, vous lui payer "+ std::toString(rent) + "$ de loyer");
		}
		else{
			player->getClient()->send("Vous êtes sur votre propriété "+land.getName())
		}
	};
};

#endif

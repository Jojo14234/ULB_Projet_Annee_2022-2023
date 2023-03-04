#ifndef _GAME_LAND_CELL_HPP
#define _GAME_LAND_CELL_HPP

#include <string>

#include "Cell.hpp"
#include "Land/Land.hpp"


class PLayer;

class LandCell : public Cell {

    Land* land;
    
	bool isOwner(Player* player) {return land->getOwner()==player;}

public: 

	LandCell(int pos, Land* land): Cell{pos}, land{land} {}
    
	void action(Player* player) {
		player->getClient()->send("Vous êtes tomber sur la propriéte"+land->getName());

		if (land->getStatus()==LAND_STATUS::FREE) {
			player->getClient()->send("La propriété est libre, voulez-vous l'acheter pour "+std::to_string(land->getPurchasePrice())+"$");
			//TO DO reception paquet
			//si achete: 
			GAME_QUERY_TYPE query;
            sf::Packet packet;

            // receive from client
            player->getClient()->receive(query, packet);

            switch (query) {
                case GAME_QUERY_TYPE::ACCEPT: land->playerPurchase(player);	//si ne peut pas ou n'achete pas -> enchere
                case GAME_QUERY_TYPE::DECLINE: player->auctionMustStart();
                
            }

		}
		else if (not this->isOwner(player) && land->getStatus()==LAND_STATUS::PAID) {
			int rent = land->getRentPrice();
			player->pay(rent, true);
			player->getClient()->send("Qui appartient à un autre joueur, vous lui payer "+ std::to_string(rent) + "$ de loyer");
			land->getOwner()->receive(rent, "autre joueur");
            if (player->getPlayerStatus() == PLAYER_STATUS::BANKRUPT){
                player->setBankruptingPlayer(land->getOwner());
            }
		}

		else if (land->getStatus() == LAND_STATUS::HYPOTEK) {

		}
		else{
			player->getClient()->send("Vous êtes sur votre propriété "+land->getName());
		}
	}
    Land* getLand(){
        return land;
    }

};

#endif

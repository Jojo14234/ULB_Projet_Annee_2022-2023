#include "../../../Player.hpp"
#include "DrawableCardCell.hpp"
#include "GoJailCell.hpp"
#include "JailCell.hpp"
#include "LandCell.hpp"
#include "ParkingCell.hpp"
#include "TaxCell.hpp"

void DrawableCardCell::action(Player* player) {
    Card* drawed_card = deck->drawACard();
    player->getClient()->send("Vous avez piocher cette carte: ");
    player->getClient()->send(drawed_card->getDesciption());
    drawed_card->action(player);
} 

void GoJailCell::action(Player* player){ 
    player->goToJail(jail);
}

void LandCell::action(Player* player) {
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
                default:
                    break;
                
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

void TaxCell::action(Player* player) {
    player->pay(tax_price, true); 
    player->getClient()->send("Tu dois payer la taxe "+name+" et tu as payé "+std::to_string(tax_price)+" euro");
}
#include "../../../Player.hpp"
#include "DrawableCardCell.hpp"
#include "GoJailCell.hpp"
#include "JailCell.hpp"
#include "LandCell.hpp"
#include "ParkingCell.hpp"
#include "TaxCell.hpp"

void DrawableCardCell::action(Player* player) {
    Card* drawed_card = deck->drawACard();
    player->getClient()->send("Vous avez pioché cette carte: ");
    player->getClient()->send(drawed_card->getDesciption());
    drawed_card->action(player);
} 

void GoJailCell::action(Player* player){ 
    player->goToJail(jail);
}

void LandCell::action(Player* player) {
		player->getClient()->send("Vous êtes tomber sur la propriéte " + land->getName());

		if (land->getStatus()==LAND_STATUS::FREE) {
			player->getClient()->send("La propriété est libre, voulez-vous l'acheter pour "+std::to_string(land->getPurchasePrice())+"e ?");

			GAME_QUERY_TYPE query;
            sf::Packet packet;
            std::string response = "";
            while (response != "yes" and response != "no") {
                player->getClient()->send("Tapez /select yes pour acheter, sinon tapez /select no.");
                player->getClient()->receive(query, packet);
                packet >> response;
                std::cout << "Response: " << response << std::endl;
            }
            if (response == "yes"){
                if (player->pay(getLand()->getPurchasePrice())){
                    player->acquireLand(getLand());
                    player->getClient()->send("Vous avez acheté cette propriété!");
                }
                else{
                    player->getClient()->send("Vous n'avez pas assez d'argent.");
                }
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
            player->getClient()->send("Cette propriété est hypothéquée. Vous ne devez donc pas payer de loyer.");
		}
		else{
			player->getClient()->send("La propriété "+ land->getName() + "vous appartient! Bienvenu chez vous ;)");
		}
}

void TaxCell::action(Player* player) {
    player->pay(tax_price, true); 
    player->getClient()->send("Tu dois payer la taxe "+name+" et tu as payé "+std::to_string(tax_price)+" euro");
}
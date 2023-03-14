#include "../../../Player/Player.hpp"
#include "DrawableCardCell.hpp"
#include "GoJailCell.hpp"
#include "JailCell.hpp"
#include "LandCell.hpp"
#include "ParkingCell.hpp"
#include "TaxCell.hpp"

void DrawableCardCell::action(Player* player) {
    Card* drawn_card = deck->drawACard();
    player->getClient()->send("Vous avez pioché cette carte : \n\t" + drawn_card->getDescription() + "\n");
    drawn_card->action(player);
} 

void GoJailCell::action(Player* player) { player->goToJail(jail); }

void LandCell::action(Player* player) {
    std::string str = "", response = "";
    str = "\nVous êtes tombé sur la propriété [" + land->getName() + "] !";
    player->getClient()->send(str);

		if (land->getStatus()==LAND_STATUS::FREE) {
            // Message concernant l'achat ou non d'une propriété
            str = "La propriété est libre, voulez-vous l'acheter pour [" + std::to_string(land->getPurchasePrice())+"e] ?";
            str += "\n - Achetez la propriété ( /select yes )";
            str += "\n - Ne pas achetez la propriété ( /select no )";
            str += "\n Dans le cas où vous n'achèteriez pas la propriété,";
            str += "\n elle sera mise au enchère pour tout le monde !\n";

            while ( response != "yes" and response != "no" ) {
                // Envois de la requête au joueur
                player->getClient()->send(str);

                // Reception de la réponse du joueur
                GAME_QUERY_TYPE query;
                sf::Packet packet;
                player->getClient()->receive(query, packet);

                // Message du joueur
                packet >> response;
            }
            // Dans le cas où le joueur souhaite acheter la propriété
            if ( response == "yes" ) {
                // Il n'a pas assez d'argents.
                if ( player->pay(this->land->getPurchasePrice()) ) {
                    player->acquireLand(getLand());
                    str = "Vous venez d'acheter la propriété [" + this->land->getName() + "]." ;
                    player->getClient()->send(str);
                }
            }
            else if ( response == "no" ) { player->getClient()->send("Vous n'avez pas achetez la propriété !"); }
		}

		else if (this->land->getStatus() == LAND_STATUS::PAID && !this->isOwner(player) ) {
			int rent = land->getRentPrice();
			player->pay(rent, true);

            str = "Cette propriété appartient à [" + this->land->getOwner()->getClient()->getAccount()->getUsername() + "]";
            str += "\nVous lui payez [" + std::to_string(rent) + "e] de loyer\n";
			player->getClient()->send(str);
			land->getOwner()->receive(rent, player->getClient()->getAccount()->getUsername());

            // TODO JOACHIM ????? ELLE FAIT QUOI CETTE LIGNE ??????
            if ( player->getPlayerStatus() == PLAYER_STATUS::BANKRUPT ) { player->setBankruptingPlayer(land->getOwner()); }
		}

		else if ( land->getStatus() == LAND_STATUS::HYPOTEK ) {
            str = "<[*_*]> Cette propriété est hypothéquée <[*_*]>\n <[*_*]> Vous ne devez donc pas payer de loyer <[ù_ù]>\n";
            player->getClient()->send(str);
		}
		else {
            str = " <[$_$]> La propriété "+ land->getName() + " vous appartient <[$_$]>\n";
			player->getClient()->send(str);
		}
}

void TaxCell::action(Player* player) {
    player->pay(tax_price, true); 
    player->getClient()->send("<[T.T]>Tu dois payer la taxe " + name + " et tu as payé " + std::to_string(tax_price) + "e ! <[T.T]>\n");
}
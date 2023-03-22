#include "../../../Player/Player.hpp"
#include "DrawableCardCell.hpp"
#include "GoJailCell.hpp"
#include "JailCell.hpp"
#include "LandCell.hpp"
#include "ParkingCell.hpp"
#include "TaxCell.hpp"
#include "../../../../Server/Game/GameServer.hpp"

void DrawableCardCell::action(Player* player) {
    Card* drawn_card = deck->drawACard();
    player->getClient()->send("Vous avez pioché cette carte : \n\t" + drawn_card->getDescription() + "\n");
    drawn_card->action(player);
} 

void GoJailCell::action(Player* player) { player->goToJail(jail); }

void LandCell::action(Player* player) {
    std::string str = "", response = "";
    str = std::to_string(player->getClient()->getGameServer()->getCurrentPlayerIndex()) + ":" + land->getName() + ":" + std::to_string(player->getBankAccount()->getMoney());
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE, str);

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
                    str = std::to_string(player->getClient()->getGameServer()->getCurrentPlayerIndex()) + ":" + land->getName() + ":" + std::to_string(player->getBankAccount()->getMoney());
                    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_BOUGHT, str);
                }
            }
            else if ( response == "no" ) { 
                player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_DIDNT_BUY, player->getUsername()); 
            }
		}

		else if (this->land->getStatus() == LAND_STATUS::PAID && !this->isOwner(player) ) {
			int rent = land->getRentPrice();
			player->pay(rent, true);
            land->getOwner()->receive(rent, player->getClient()->getAccount()->getUsername());

            str = std::to_string(rent) + ":";
            str += std::to_string(player->getIndex()) + ":";
            str += std::to_string(player->getMoney()) + ":";
            str += std::to_string(this->land->getOwner()->getIndex()) + ":";
            str += std::to_string(this->land->getOwner()->getMoney());
            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_PAID_PLAYER, str); 


            // TODO JOACHIM ????? ELLE FAIT QUOI CETTE LIGNE ??????
            if ( player->getStatus() == PLAYER_STATUS::BANKRUPT_SUSPECTED ) { player->setPlayerToRefund(land->getOwner()); }
		}

		else if ( land->getStatus() == LAND_STATUS::HYPOTEK ) {
            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL, player->getUsername() + ":" + land->getOwner()->getUsername()); 
		}
		else {
            player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL, player->getUsername()); 
		}
}

void TaxCell::action(Player* player) {
    player->pay(tax_price, true); 
    std::string str = name + ":" + std::to_string(tax_price) + ":" + std::to_string(player->getIndex()) + ":" + std::to_string(player->getMoney()); 
    player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE_ON_OWN_CELL, str); 
}
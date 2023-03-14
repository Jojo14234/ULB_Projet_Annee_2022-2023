#include "JailCard.hpp"
#include "../../../Player/Player.hpp"
#include "../../../../Server/ClientManager/ClientManager.hpp"


void JailCard::action(Player* player) {
	this->setOwner(player);
	player->acquireGOOJCard(this);
	player->getClient()->send("Vous avez reçu une carte sortie de prison");
}

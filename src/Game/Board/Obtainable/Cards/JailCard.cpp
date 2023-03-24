#include "JailCard.hpp"
#include "../../../Player/Player.hpp"


void JailCard::action(Player* player) {
	this->setOwner(player);
	player->acquireGOOJCard(this);
	player->getClient()->sendQueryMsg("", QUERY::GET_GO_OUT_JAIL_CARD);
}

void JailCard::use() {
    this->owner->setStatus(PLAYER_STATUS::FREE);
    this->owner->removeOneGoOutOfJailCard(this);
    this->owner->getClient()->sendQueryMsg("", QUERY::LOST_GO_OUT_JAIL_CARD);
    this->setOwner(nullptr);
}

#include "JailCard.hpp"
#include "../../../Player/Player.hpp"


void JailCard::action(Player* player) {
	this->setOwner(player);
	player->acquireGOOJCard(this);
}

void JailCard::use() {
    this->owner->setStatus(PLAYER_STATUS::FREE);
    this->owner->removeOneGoOutOfJailCard(this);
    this->owner->getClient()->sendQueryMsg(std::to_string(owner->getIndex()+1), QUERY::LOST_GO_OUT_JAIL_CARD);
    this->setOwner(nullptr);
}

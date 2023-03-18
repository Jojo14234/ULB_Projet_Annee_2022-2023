#include "CellCard.hpp"
#include "../../../../Server/Game/GameServer.hpp"

#include "../../../Player/Player.hpp"

void CellCard::action(Player* player) {
    player->getClient()->send("Vous vous déplacez à la case "+ std::to_string(this->dest));
    player->move(player->getClient()->getGameServer()->getGame()->getBoard()[this->dest], gain_money);	//get cell by index
    player->getCurrentCell()->action(player);
}

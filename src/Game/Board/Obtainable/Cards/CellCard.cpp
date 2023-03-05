#include "CellCard.hpp"
#include "../../../../Server/Game/GameServer.hpp"

#include "../../../Player.hpp"

void CellCard::action(Player* player) {
    player->getClient()->send("Vous vous déplacez à la case "+ std::to_string(dest));
    player->move(player->getClient()->getGameServer()->getGame()->getBoard()->getCellByIndex(dest), gain_money);	//get cell by index
};
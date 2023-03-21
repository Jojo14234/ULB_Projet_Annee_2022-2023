#include "CellCard.hpp"
#include "../../../../Server/Game/GameServer.hpp"

#include "../../../Player/Player.hpp"

void CellCard::action(Player* player) {
    player->getClient()->send("Vous vous déplacez à la case "+ std::to_string(this->dest));
    player->move(player->getClient()->getGameServer()->getGame()->getBoard()[this->dest], gain_money);	//get cell by index
    player->getCurrentCell()->action(player);
}

void MoveBackCellCard::action(Player* player){
        int current_pos = player.getCurrentCell().getPosition();
        this->setDest(current_pos-step_back);
        this->CellCard::action();
}

void NearestCellCard::action(Player* player){
        int current_pos = player.getCurrentCell().getPosition();
        std::array<int, 4> dest_pos = this->makeDestArray(current_pos);
        int nearest_dest = this->searchMinIdx(dest_pos);
        this->setDest(nearest_dest);
        this->CellCard::action();
}

int NearestCellCard::searchMinIdx(std::array<int, 4> dest_pos) {
    int min_idx = 0;
    for (int i=0; i<4, i++){
        if (dest_pos[i] > 0) {
            if (dest_pos[i] < dest_pos[min_idx]) {
                min_idx = i;
            }
        }
    }
    return min_idx;
}

std::array<int, 4> NearestCellCard::makeDestArray(int current_pos) {
    std::array<int, 4> dest_pos;
    for (int i=0; i<4; i++){
        dest_pos[i] = this->near_pos[i] - current_pos;
    }
    return dest_pos;
}
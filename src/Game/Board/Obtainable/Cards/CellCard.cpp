#include "CellCard.hpp"

#include "../../../../Server/Game/GameServer.hpp"
#include "../../../Player/Player.hpp"

/*
 * Check si la destination est négative au quelle cas re-calcul une destination
 * Déplace le joueur
 * SI le joueur tombe en prison, il devient prisonnier
 * Sinon il peut simplement effectué l'action de la nouvelle case sur laquelle il se trouve
 */
void CellCard::action(Player *player) {
    // On vérifie si la destination est négative, on calcule la position de destination
    if ( this->destination < 0 ) { this->destination = ( player->getPosition() - std::abs(this->destination) + BOARD_SIZE ) % BOARD_SIZE; }
    // Message pour l'affichage
    player->getClient()->sendQueryMsg(std::to_string(this->destination), QUERY::INFOS_CARD_CELL_TO_GO);
    // Case de destination
    Cell* destination_cell = player->getClient()->getGameServer()->getGame()->getBoard()[this->destination];
    // Déplacement du joueur
    player->processMove(destination_cell, this->receive_money);
    // Si joueur est en prison, il devient prisonnier
    if ( this->destination == PRISON_INDEX ) { 
        player->setStatus(PLAYER_STATUS::JAILED); 
        player->getClient()->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_SEND_TO_PRISON, player->getUsername());
    }
    // Sinon il exécute l'action de la case.
    else { player->getCurrentCell()->action(player); }
}

/*
 * Cherche la gare la plus proche et met indexe dans l'attribut destination
 * Appelle CellCard::action
 */
void NearestCellCard::action(Player* player){
        int nearestStation = this->findNearestStation(player->getCurrentCell()->getPosition());
        this->setDest(nearestStation);
        this->CellCard::action(player);
}

/*
 * Renvoie la position de la gare la plus proche dans un vecteur de x gare
 * par rapport à la position actuelle en sachant qu'on ne peut que avancer
 */
int NearestCellCard::findNearestStation(int current_pos) {
    int nearestStation = this->stations[0];
    int shorterPath = (nearestStation - current_pos + BOARD_SIZE) % BOARD_SIZE;
    for (unsigned int i = 1; i < this->stations.size(); i++) {
        int path = (this->stations[i] - current_pos + BOARD_SIZE) % BOARD_SIZE;
        if ( path < shorterPath ) {
            shorterPath = path;
            nearestStation = this->stations[i];
        }
    }
    return nearestStation;
}
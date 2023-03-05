#include "../../../../Player.hpp"
#include "Land.hpp"
#include "Property.hpp"
#include "../../../../../Server/ClientManager/ClientManager.hpp"


void Property::playerPurchase(Player* player) {
    Land::playerPurchase(player);
    player->acquireProperty(*this);
}

bool Property::build(Player* player) {    //renvoie false si n'arrive pas à construire
    //verif couleur et tous même niveau +/- et aucune hypothéquer
    //verif owner
    //verif level max

    if (this->owner != player){
        player->getClient()->send("Vous n'êtes pas propriétaire de cette propriété (construction refusée)");
        return false;
    }

    else if (this->getLevel()==PROPERTY_LEVEL::HOTEL){   //niveau max
        player->getClient()->send("Le niveau max de construction est atteint");
        return false;
    }

    else if (not this->checkTransaction(player, true)) {
        player->getClient()->send("Pas toute couleur ou pas bon niveau");
        return false;
    }

    if (player->pay(this->construct_price)){
        this->levelUp();
        player->getClient()->send("Vous buildez comme Bob the builder, bravo");
        return true;
    }
}

bool Property::sellBuilding(Player* player){
    if (this->owner != player){
        player->getClient()->send("Vous n'êtes pas propriétaire de cette propriété (vente refusée)");
        return false;
    }
    else if (not this->checkTransaction(player, false)) {
        player->getClient()->send("Les niveaux de vos construction ne sont pas équilibrée");
        return false;
    }

    else {
        player->receive(this->purchase_price/2, "Bank");
        this->levelDown();
        player->getClient()->send("Vous avez vendu un batiment de votre propriété à moitié prix");
        return true;
    }
}

bool Property::checkTransaction(Player* player, bool is_building){
    std::vector<Property*> player_props =  player->getAllProperties();
    int other_props;
    if (this->color == PROPERTY_COLOR::BROWN or this->color == PROPERTY_COLOR::DARK_BLUE) { other_props = 1;}
    else { other_props = 2;}

    std::vector<Property*> same_color = this->getSameColorBuilding(player_props);

    if (is_building) {
        if (same_color.size() == other_props) {
            player->getClient()->send("Vous avez toutes les propriétés de cette couleur");

            int potential_level = static_cast<int>(this->level)+1;
            if (this->hasGoodLevel(potential_level, same_color)) {
                player->getClient()->send("Vous pouvez construire (bon niveau aux autres construction");
                return true;
            }
            else {
                player->getClient()->send("Vos niveaux ne sont pas équilibré, vous ne pouvez pas construire.");
                return false;
            }
        }
        else {
            player->getClient()->send("Vous n'avez pas toutes les propriétés de ce groupe de couleur (pas de construction possible)");
            return false;
        }
    }

    //sell buildings
    else {
        int potential_level = static_cast<int>(this->level)-1;
        if (this->hasGoodLevel(potential_level, same_color)) {
            player->getClient()->send("Vous avez des niveaux équilibrée");
            return true;
        }
        else {
            player->getClient()->send("Niveau pas équilibrée si vous vendez cette propriété");
            return false;
        }
    }

}


std::vector<Property*> Property::getSameColorBuilding(std::vector<Property*> player_props){
    std::vector<Property*> same_color;
    for (auto &elem: player_props) {
        if (elem->getColor() == this->color) {
            same_color.push_back(elem);
        }
    }
    return same_color;
}

bool Property::hasGoodLevel(int potential_level, std::vector<Property*> same_color) {
    bool good_level;
    if (same_color.size() == 1){
        int other_level = same_color[0]->getIntLevel();
        good_level = (abs(other_level-potential_level) <= 1);
    }
    else if(same_color.size() == 2){
        int other1_level = same_color[0]->getIntLevel();
        int other2_level = same_color[1]->getIntLevel();
        good_level = ((abs(other1_level-potential_level) <= 1) and (abs(other2_level-potential_level) <= 1));
    }
    else if (same_color.size()==0) {
        good_level = true;
    }
    return good_level;
}

/*bool Property::checkBuild(Player* player) {
    std::vector<Property*> player_props =  player->getAllProperties();
    int other_props;
    if (this->color == PROPERTY_COLOR::BROWN or this->color == PROPERTY_COLOR::DARK_BLUE) { other_props = 1;}
    else { other_props = 2;}

    int count = 0;
    std::vector<Property*> same_color;
    for (auto &elem: player_props) {
        if (elem->getColor() == this->color) {
            count++;
            same_color.push_back(elem);
        }
    }
    if (count==other_props){
        player->getClient()->send("Vous avez toutes les propriétés de cette couleur")
        int potential_level = static_cast<int>((this->level)+1);
        bool good_level = false;

        if (other_props == 1){
            int other_level = static_cast<int>(same_color[0]->getIntLevel());
            good_level = (abs(other_level-potential_level) <= 1);
        }
        else if(other_props == 2){
            int other1_level = static_cast<int>(same_color[0]->getIntLevel());
            int other2_level = static_cast<int>(same_color[1]->getIntLevel());
            good_level = ((abs(other1_level-potential_level) <= 1) and (abs(other2_level-potential_level) <= 1));
        }
        if (good_level) {
            player->getClient()->send("Vous pouvez construire (bon niveau aux autres construction")
            return true;
        }
        else {
            player->getClient()->send("Vos niveaux ne sont pas équilibré, vous ne pouvez pas construire.")
            return false;
        }
    }
    else {
        player->getClient()->send("Vous n'avez pas toutes les propriétés de ce groupe de couleur (pas de construction possible)"
        return false;
    }
}*/

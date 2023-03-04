#include "../../../../Player.hpp"
#include "Land.hpp"
#include "Property.hpp"

void Property::playerPurchase(Player* player) {
    Land::playerPurchase(player);
    player->acquireProperty(this);
}

bool Property::build(Player* player) {    //renvoie false si n'arrive pas à construire
    //verif couleur et tous même niveau +/- et aucune hypothéquer
    //verif owner
    //verif level max

    if (this->owner != player){
        player->getClient()->send("Vous n'êtes pas propriétaire de cette propriété (construction refusée"))
        return false;
    }

    else if (this->getLevel()==PROPERTY_LEVEL::HOTEL){   //niveau max
        player->getClient()->send("Le niveau max de construction est atteint");
        return false;
    }

    else if (not this->checkBuild()) {
        player->getClient()->send"Pas toute couleur ou pas bon niveau");
        return false;
    }

    if (player->pay(this->construct_price)){
        player->getClient()->send("Vous buildez comme Bob the builder, bravo")
        this->levelUp();
        return true;
    }
}

bool Property::checkBuild(Player* player) {
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
}

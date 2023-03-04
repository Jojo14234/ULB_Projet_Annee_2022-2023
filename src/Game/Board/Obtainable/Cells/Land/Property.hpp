#ifndef _GAME_PROPERTY_HPP
#define _GAME_PROPERTY_HPP

#include <string>
#include <array>
#include <json/json.h>
#include "../../../../../utils/Configs.hpp"

#include "Land.hpp"


class Player;

enum class PROPERTY_LEVEL {EMPTY=0, ONE=1, TWO=2, THREE=3, FOUR=4, HOTEL=5};


class Property : Land {
    
	PROPERTY_COLOR color;
    
	std::array<int, 6> rent_prices;
	int construct_price;
    
	PROPERTY_LEVEL level = PROPERTY_LEVEL::EMPTY;

	int getRentPrice() { return this->rent_prices[static_cast<int>(this->level)]; }
    
	void levelUp() { int actual=static_cast<int>(this->level); this->level = static_cast<PROPERTY_LEVEL>(actual+1)};

    PROPERTY_COLOR getColor() { return this->color; }

    bool checkBuild(Player* player) {
        std::vector<Property*> player_props =  player->getAllProperties();
        int other_props;
        if (this->color == PROPERTY_COLOR::BROWN or this->color == PROPERTY_COLOR::DARK_BLUE) { other_props = 1;}
        else { other_props = 2;}

        int count = 0;
        std::vector<Property*> same_color;
        for (auto &elem: player_props) {
            if (elem->getColor() == this->color) {
                count++;
                same_color.push_back(elem)
            }
        }
        if (count==other_props){
            player->getClient()->send("Vous avez toutes les propriétés de cette couleur")
            int potential_level = int potential_level(this->level)++;
            bool good_level = false;

            if (other_props == 1){
                int other_level = static_cast<int>(same_color[0]->getLevel());
                good_level = (abs(other_level-potential_level) <= 1);
            }
            else if(other_props == 2){
                int other1_level = static_cast<int>(same_color[0]->getLevel());
                int other2_level = static_cast<int>(same_color[1]->getLevel());
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

public:
    
	Property(Json::Value prop_info):  Land{prop_info}, color{static_cast<PROPERTY_COLOR>(prop_info["color"].asInt())},  construct_price{prop_info["construct price"].asInt()}{
		for (int i = 0; i<6; i++) this->rent_prices[i] = prop_info["rent prices"][i].asInt();
	}

	void playerPurchase(Player* player);

	int getLevel() { return static_cast<int>(level); }

    bool build(player* Player) {    //renvoie false si n'arrive pas à construire
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

};

#endif

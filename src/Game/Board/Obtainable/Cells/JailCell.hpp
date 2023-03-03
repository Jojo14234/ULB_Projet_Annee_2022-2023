#ifndef _GAME_JAIL_CELL_HPP
#define _GAME_JAIL_CELL_HPP

#include <string>

#include "Cell.hpp"


class Player;

class JailCell: public Cell{
    
	bool outWithMoney(Player* player, bool forced) {
        if (player->pay(50, forced)){
            player->exitJail(); 
            player->getClient()->send("Vous êtes sorti de prison !");
            return true;
        }
        else{
            return false;   //true fin du tour ou bien continue avec autre choix ?
        }
        
    }    //laisse le choix
    
	void outWithCard(Player* player) {
        bool free = false;
        if (player->hasGOOJCards()){
            free = true;
        }
        else{   //enchere
            //boucle sur tout les joueurs ? jusqu'a free ou check tous les joueurs
            //demande si achat
            //si concluant, free
        }

        if (free) {
            player->exitJail();
            player->looseGOOJCard();
            player->getClient()->send("Vous êtes sorti de prison !");
        }
    }
    
	void outWithDice(Player* player, Dice dice) {}
        player->addRollInPrison();
        if (dice.isDouble()){
            player->getClient()->send("Vous êtes sorti de prison !");
            return true;
        }
        else if (player->getRollsInPrison() == 3;) {
            return this->outWithMoney(player, true);
        }
        else { return true;}
        
    }; 
                //force à payer -> potentiel faillite
    
	void out();

public:

	JailCell(int pos);
    
	void action(Player* player){
        if (player->isInJail()){    // y'avais un !
            player->getClient()->send("Vous êtes en prison, tapez /roll, /usecard ou /pay pour essayer de sortir.");
            player->getClient()->send("Vous possédez " + std::to_string(player->hasGOOJCards()) + " cartes pour sortir de prison.");

            GAME_QUERY_TYPE query;
            sf::Packet packet;

            // receive from client
            player.getClient().receive(query, packet);

            bool end_round = false;

            while (not end_round) {
                switch (query) {
                case GAME_QUERY_TYPE::PAY:{
                    end_round = outWithMoney(player, false);
                    break;
                }
                case GAME_QUERY_TYPE::USEGOOJCARD: {
                    end_round = outWithCard(player);
                    break;
                }
                case GAME_QUERY_TYPE::ROLL_DICE: {
                    Dice dice = Dice();
                    end_round = outWithDice(player, dice);
                    // if (free) dice.getResult play
                    break;
                } 
                
            }
        }
        else {
            player->getClient().send("Vous visitez la prison, il ne vous arrive rien.");
        }
    };    //envoyer demande de choix au client (reception, receive)
};
#endif

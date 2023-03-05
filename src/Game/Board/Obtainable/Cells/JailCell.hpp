#ifndef _GAME_JAIL_CELL_HPP
#define _GAME_JAIL_CELL_HPP

#include <string>

#include "Cell.hpp"


class Player;

class JailCell: public Cell{
    
	bool outWithMoney(Player* player, bool forced) {
        if (player->pay(50, forced)){   //si n'arrive pas a payer
            player->exitJail(); 
            player->getClient()->send("Vous êtes sorti de prison !");
            return true;
        }
        else if(forced==false){
            return false;   //s'il a fait le choix de payer mais pas assez d'argent
                            //continue à choisir un moyen de sortir de prison
                            //(otherwise c'est bankrupt)
        }
        
    }   
    
	bool outWithCard(Player* player) {
        if (player->hasGOOJCards()){
            player->exitJail();
            player->looseGOOJCard();
            player->getClient()->send("Vous êtes sorti de prison !");
            return true;
        }
        else{   //echange demandé depuis prison, mettre à jour le player et sortie de boucle (boucle echange lancé dans game server)
            player->exchangeFromJail()  //achete ou non une carte 
            return false;   //retour à la boucle de choix, si le joueur a acheter une carte, peut l'utiliser en choississant l'option GOOJ
        }

    }
    
	bool outWithDice(Player* player, Dice dice){ //test les dés et apres fin du tour
        player->addRollInPrison();
        if (dice.isDouble()){
            player->exitJail();
            player->getClient()->send("Vous êtes sorti de prison !");
            //penser à une méthode pour que le joueur joue (si pas le temps, juste freed et tour du joueur suivantS)
            return true;
        }
        else if (player->getRollsInPrison() == 3;) {
            return this->outWithMoney(player, true);
        }
        else { return true;}    //si pas de double mais que pas le 3e lancée, fin du tour du joueur
        
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
            player.getClient()->receive(query, packet);

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

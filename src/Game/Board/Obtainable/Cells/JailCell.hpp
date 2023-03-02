#ifndef _GAME_JAIL_CELL_HPP
#define _GAME_JAIL_CELL_HPP

#include <string>

#include "Cell.hpp"


class Player;

class JailCell: public Cell{
    
	void outWithMoney(Player* player) {player->pay(50); player->exitJail();};    //laisse le choix
    
	void outWithCard();
    
	void outWithDice(); //force à payer -> potentiel faillite
    
	void out();

public:

	JailCell(int pos);
    
	void action(Player* player){
        if (!player->isInJail()){
            player->getClient().send("Vous êtes en prison, tapez /roll, /usecard ou /pay pour essayer de sortir.");
            player->getClient()->send("Vous possédez " + std::to_string(player->hasGOOJCards()) + " cartes pour sortir de prison.");

            GAME_QUERY_TYPE query;
            sf::Packet packet;

            // receive from client
            player.getClient().receive(query, packet);

            switch (query) {
                case GAME_QUERY_TYPE::ROLL_DICE: fuihgih;
                case GAME_QUERY_TYPE::PAY: fffuhiufh;
                case GAME_QUERY_TYPE::USEGOOJCARD
            }
        }
        else {
            player->getClient().send("Vous visitez la prison, il ne vous arrive rien.");
        }
    };    //envoyer demande de choix au client (reception, receive)
};
#endif

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
        player->getClient()->send(""); //TODO
    };    //envoyer demande de choix au client (reception, receive)

};
#endif

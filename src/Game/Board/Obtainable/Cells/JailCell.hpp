#ifndef _GAME_JAIL_CELL_HPP
#define _GAME_JAIL_CELL_HPP

#include <string>

#include "Cell.hpp"


class Player;

class JailCell: public Cell {

    bool outWithMoney(Player *player, bool forced);

    bool outWithCard(Player *player);

    bool outWithDice(Player *player, Dice dice);
    //force à payer -> potentiel faillite

public:

    using Cell::Cell;

    void action(Player *player) override;
};
#endif
